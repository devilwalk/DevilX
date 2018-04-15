#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::CFBXProcesser::CFBXProcesser(CFBXResource * res)
	:mResource(res)
	,mCommonProcesser(nullptr)
	,mRenderProcesser(nullptr)
{
	mCommonProcesser=DEVILX_NEW CFBXCommonProcesser(this);
	mRenderProcesser=DEVILX_NEW CFBXRenderProcesser(this);
}

NSDevilX::NSResourceSystem::CFBXProcesser::~CFBXProcesser()
{
	DEVILX_DELETE(mCommonProcesser);
}

Void NSDevilX::NSResourceSystem::CFBXProcesser::process(NSRenderSystem::IEntity * entity,Bool sync)
{

	struct SRenderCallback
		:public CResource::SLoadCallback
		,public TBaseObject<SRenderCallback>
	{
		CFBXProcesser * const mProcesser;
		const Bool mSync;
		NSRenderSystem::IEntity * const mEntity;
		SRenderCallback(CFBXProcesser * processer,Bool sync,NSRenderSystem::IEntity * entity)
			:mProcesser(processer)
			,mSync(sync)
			,mEntity(entity)
		{}
		virtual Void onLoaded(CResource * res) override final
		{
			mProcesser->_process(mEntity);
		}
	};
	struct SCommonCallback
		:public CResource::SLoadCallback
		,public TBaseObject<SCommonCallback>
	{
		CFBXProcesser * const mProcesser;
		const Bool mSync;
		NSRenderSystem::IEntity * const mEntity;
		SCommonCallback(CFBXProcesser * processer,Bool sync,NSRenderSystem::IEntity * entity)
			:mProcesser(processer)
			,mSync(sync)
			,mEntity(entity)
		{}
		virtual Void onLoaded(CResource * res) override final
		{
			mProcesser->getRenderProcesser()->load(&SRenderCallback(mProcesser,mSync,mEntity),mSync);
		}
	};
	mCommonProcesser->load(&SCommonCallback(this,sync,entity),sync);
}

Void NSDevilX::NSResourceSystem::CFBXProcesser::_process(NSRenderSystem::IEntity * entity)
{
	for(auto i=0;i<mRenderProcesser->getMeshes().size();++i)
	{
		auto & mesh=mRenderProcesser->getMeshes()[i];
		auto geo=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry(entity->queryInterface_ISceneElement()->getName()+CStringConverter::toString(i));
		geo->getVertexBuffer()->setCount(static_cast<UInt32>(mesh.mVertices.size()));
		CFloat3 * positions=static_cast<CFloat3*>(DEVILX_ALLOC(sizeof(CFloat3)*mesh.mVertices.size()));
		for(SizeT i=0;i<mesh.mVertices.size();++i)
		{
			positions[i]=CFloat3(static_cast<Float>(mesh.mVertices[i].mPosition[0]),static_cast<Float>(mesh.mVertices[i].mPosition[1]),static_cast<Float>(mesh.mVertices[i].mPosition[2]));
		}
		geo->getVertexBuffer()->setPositions(positions);
		if(mesh.mVertices[0].hasNormal())
		{
			CFloat3 * normals=static_cast<CFloat3*>(DEVILX_ALLOC(sizeof(CFloat3)*mesh.mVertices.size()));
			for(SizeT i=0;i<mesh.mVertices.size();++i)
			{
				normals[i]=CFloat3(static_cast<Float>(mesh.mVertices[i].mNormal[0]),static_cast<Float>(mesh.mVertices[i].mNormal[1]),static_cast<Float>(mesh.mVertices[i].mNormal[2]));
			}
			geo->getVertexBuffer()->setNormals(normals);
		}
		if(mesh.mVertices[0].hasTangent())
		{
			CFloat3 * tangents=static_cast<CFloat3*>(DEVILX_ALLOC(sizeof(CFloat3)*mesh.mVertices.size()));
			for(SizeT i=0;i<mesh.mVertices.size();++i)
			{
				tangents[i]=CFloat3(static_cast<Float>(mesh.mVertices[i].mTangent[0]),static_cast<Float>(mesh.mVertices[i].mTangent[1]),static_cast<Float>(mesh.mVertices[i].mTangent[2]));
			}
			geo->getVertexBuffer()->setTangents(tangents);
		}
		if(mesh.mVertices[0].hasUV0())
		{
			CFloat2 * uvs=static_cast<CFloat2*>(DEVILX_ALLOC(sizeof(CFloat2)*mesh.mVertices.size()));
			for(SizeT i=0;i<mesh.mVertices.size();++i)
			{
				uvs[i]=CFloat2(static_cast<Float>(mesh.mVertices[i].mUV0[0]),static_cast<Float>(mesh.mVertices[i].mUV0[1]));
			}
			geo->getVertexBuffer()->setTextureCoords(uvs);
		}
		if(mesh.mVertices[0].hasUV1())
		{
			CFloat2 * uvs=static_cast<CFloat2*>(DEVILX_ALLOC(sizeof(CFloat2)*mesh.mVertices.size()));
			for(SizeT i=0;i<mesh.mVertices.size();++i)
			{
				uvs[i]=CFloat2(static_cast<Float>(mesh.mVertices[i].mUV1[0]),static_cast<Float>(mesh.mVertices[i].mUV1[1]));
			}
			geo->getVertexBuffer()->setTextureCoords(uvs,NSRenderSystem::IEnum::ETextureCoord_1);
		}
		if(mesh.mVertices[0].hasSkin())
		{
			CFloat4 * blend_weights=static_cast<CFloat4*>(DEVILX_ALLOC(sizeof(CFloat4)*mesh.mVertices.size()));
			UInt8 * blend_indices=static_cast<UInt8*>(DEVILX_ALLOC(sizeof(UInt8)*4*mesh.mVertices.size()));
			for(SizeT i=0;i<mesh.mVertices.size();++i)
			{
				struct SFindIf
				{
					fbxsdk::FbxCluster * const mCluster;
					SFindIf(fbxsdk::FbxCluster * cluster)
						:mCluster(cluster)
					{}
					Boolean operator()(const CFBXCommonProcesser::SBone & bone)const
					{
						return bone.isMatch(mCluster);
					}
				};
				blend_weights[i]=CFloat4::sZero;
				for(SizeT j=0;j<mesh.mVertices[i].mSkinInfos.size();++j)
				{
					SFindIf find_if_func(mesh.mVertices[i].mSkinInfos[j].mCluster);
					blend_indices[i*4+j]=std::find_if(mCommonProcesser->getBones().begin(),mCommonProcesser->getBones().end(),find_if_func)-mCommonProcesser->getBones().begin();
					blend_weights[i][j]=mesh.mVertices[i].mSkinInfos[j].mWeight;
				}
			}
			geo->getVertexBuffer()->setBlendWeights(blend_weights);
			geo->getVertexBuffer()->setBlendIndices(blend_indices);
		}
		geo->getIndexBuffer()->setCount(static_cast<UInt32>(mesh.mIndices.size()));
		UInt32 * indices_buf=static_cast<UInt32*>(DEVILX_ALLOC(sizeof(UInt32)*mesh.mIndices.size()));
		memcpy(indices_buf,&mesh.mIndices[0],sizeof(UInt32)*mesh.mIndices.size());
		geo->getIndexBuffer()->setIndices(indices_buf);

		auto sub_entity=entity->createSubEntity(CStringConverter::toString(entity->getSubEntityCount()));
		sub_entity->setGeometry(geo);
		sub_entity->queryInterface_IGeometryUsage()->setVertexBufferOffset(0);
		sub_entity->queryInterface_IGeometryUsage()->setVertexCount(static_cast<UInt32>(mesh.mVertices.size()));
		sub_entity->queryInterface_IGeometryUsage()->setIndexBufferOffset(0);
		sub_entity->queryInterface_IGeometryUsage()->setIndexCount(static_cast<UInt32>(mesh.mIndices.size()));
		sub_entity->queryInterface_IGeometryUsage()->setOperationType(NSRenderSystem::IEnum::EOperationType_TriangleList);
		sub_entity->setRenderable(true);
		sub_entity->setAmbientModel(NSRenderSystem::IEnum::EMaterialAmbientModel_Constant);
		sub_entity->setDiffuseModel(NSRenderSystem::IEnum::EMaterialDiffuseModel_Lambert);
		sub_entity->getDiffuseColourUnitState()->setEnable(true);
		CFloatRGB diffuse(static_cast<Float>(mesh.mMaterial->Diffuse.Get()[0]),static_cast<Float>(mesh.mMaterial->Diffuse.Get()[1]),static_cast<Float>(mesh.mMaterial->Diffuse.Get()[2]));
		sub_entity->getDiffuseColourUnitState()->setValue(CFloatRGB(diffuse*static_cast<Float>(mesh.mMaterial->DiffuseFactor.Get())));
		if(mesh.mMaterial->GetClassId()==fbxsdk::FbxSurfacePhong::ClassId)
		{
			auto phong=static_cast<fbxsdk::FbxSurfacePhong*>(mesh.mMaterial);
			sub_entity->setSpecularModel(NSRenderSystem::IEnum::EMaterialSpecularModel_Phong);
			sub_entity->getSpecularColourUnitState()->setEnable(true);
			CFloatRGB specular(static_cast<Float>(phong->Specular.Get()[0]),static_cast<Float>(phong->Specular.Get()[1]),static_cast<Float>(phong->Specular.Get()[2]));
			sub_entity->getSpecularColourUnitState()->setValue(CFloatRGB(specular*static_cast<Float>(phong->SpecularFactor.Get())));
			sub_entity->getSpecularPowerUnitState()->setEnable(true);
			sub_entity->getSpecularPowerUnitState()->setValue(static_cast<Float>(phong->Shininess.Get()));
		}
		assert(mesh.mMaterial->Diffuse.GetSrcObjectCount<fbxsdk::FbxTexture>()<=1);
		if(mesh.mMaterial->Diffuse.GetSrcObject<fbxsdk::FbxTexture>())
		{
			if(mesh.mMaterial->Diffuse.GetSrcObject<fbxsdk::FbxTexture>()->GetClassId()==fbxsdk::FbxFileTexture::ClassId)
			{
				auto file_tex=mesh.mMaterial->Diffuse.GetSrcObject<fbxsdk::FbxFileTexture>();
				IResourceImp * res=nullptr;
				if(file_tex->GetFileName())
				{
					res=static_cast<IResourceImp*>(ISystemImp::getSingleton().createOrRetrieveResource(file_tex->GetFileName(),file_tex->GetFileName()));
				}
				else if(file_tex->GetRelativeFileName())
				{
					String abs_path=CDirectory::getDirectoryName(CDirectory::getAbsolutePath(mResource->getFileName()));
					abs_path+=file_tex->GetRelativeFileName();
					res=static_cast<IResourceImp*>(ISystemImp::getSingleton().createOrRetrieveResource(abs_path,abs_path));
				}
			}
			else if(mesh.mMaterial->Diffuse.GetSrcObject<fbxsdk::FbxTexture>()->GetClassId()==fbxsdk::FbxLayeredTexture::ClassId)
			{
				assert(false);
			}
			else if(mesh.mMaterial->Diffuse.GetSrcObject<fbxsdk::FbxTexture>()->GetClassId()==fbxsdk::FbxProceduralTexture::ClassId)
			{
				assert(false);
			}
		}
	}
}
