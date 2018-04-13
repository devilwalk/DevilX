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
	struct SCommonCallback
		:public CResource::SLoadCallback
		,public TBaseObject<SCommonCallback>
	{
		CFBXProcesser * mProcesser;
		virtual Void onLoaded(CResource * res) override final
		{
			mProcesser->
		}
	};
	mCommonProcesser->load(&SCommonCallback(),sync);
	auto geo=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry(entity->queryInterface_ISceneElement()->getName());
	geo->getVertexBuffer()->setCount(static_cast<UInt32>(vertices.size()));
	CFloat3 * positions=static_cast<CFloat3*>(DEVILX_ALLOC(sizeof(CFloat3)*vertices.size()));
	for(SizeT i=0;i<vertices.size();++i)
	{
		positions[i]=CFloat3(static_cast<Float>(vertices[i].mPosition[0]),static_cast<Float>(vertices[i].mPosition[1]),static_cast<Float>(vertices[i].mPosition[2]));
	}
	geo->getVertexBuffer()->setPositions(positions);
	CFloat3 * normals=static_cast<CFloat3*>(DEVILX_ALLOC(sizeof(CFloat3)*vertices.size()));
	for(SizeT i=0;i<vertices.size();++i)
	{
		normals[i]=CFloat3(static_cast<Float>(vertices[i].mNormal[0]),static_cast<Float>(vertices[i].mNormal[1]),static_cast<Float>(vertices[i].mNormal[2]));
	}
	geo->getVertexBuffer()->setNormals(normals);
	CFloat2 * uv0s=static_cast<CFloat2*>(DEVILX_ALLOC(sizeof(CFloat2)*vertices.size()));
	for(SizeT i=0;i<vertices.size();++i)
	{
		uv0s[i]=CFloat2(static_cast<Float>(vertices[i].mUV0[0]),static_cast<Float>(vertices[i].mUV0[1]));
	}
	geo->getVertexBuffer()->setTextureCoords(uv0s);
	CFloat4 * blend_weights=static_cast<CFloat4*>(DEVILX_ALLOC(sizeof(CFloat4)*vertices.size()));
	UInt8 * blend_indices=static_cast<UInt8*>(DEVILX_ALLOC(sizeof(UInt8)*4*vertices.size()));
	for(SizeT i=0;i<vertices.size();++i)
	{
		Float weights[]={0,0,0,0};
		UInt8 index[]={255,255,255,255};
		auto j=0;
		for(auto const & skin_info:vertices[i].mSkinInfos)
		{
			index[j]=cluster_indices.get(skin_info.mCluster);
			weights[j++]=skin_info.mWeight;
		}
		blend_weights[i]=CFloat4(weights[0],weights[1],weights[2],weights[3]);
		for(auto j=0;j<4;j++)
			blend_indices[i*4+j]=index[j];
	}
	geo->getVertexBuffer()->setBlendWeights(blend_weights);
	geo->getVertexBuffer()->setBlendIndices(blend_indices);
	geo->getIndexBuffer()->setCount(static_cast<UInt32>(indices.size()));
	UInt32 * indices_buf=static_cast<UInt32*>(DEVILX_ALLOC(sizeof(UInt32)*indices.size()));
	memcpy(indices_buf,&indices[0],sizeof(UInt32)*indices.size());
	geo->getIndexBuffer()->setIndices(indices_buf);

	UInt32 index_start=0;
	UInt32 vertex_start=0;
	for(const auto & mesh_info:mesh_infos)
	{
		for(SizeT i=0;i<mesh_info.mMaterials.size();++i)
		{
			auto sub_entity=entity->createSubEntity(CStringConverter::toString(entity->getSubEntityCount()));
			sub_entity->setGeometry(geo);
			sub_entity->queryInterface_IGeometryUsage()->setVertexBufferOffset(vertex_start);
			sub_entity->queryInterface_IGeometryUsage()->setVertexCount(static_cast<UInt32>(mesh_info.mVerticesByMaterial[i].size()));
			sub_entity->queryInterface_IGeometryUsage()->setIndexBufferOffset(index_start);
			sub_entity->queryInterface_IGeometryUsage()->setIndexCount(static_cast<UInt32>(mesh_info.mIndicesByMaterial[i].size()));
			sub_entity->queryInterface_IGeometryUsage()->setOperationType(NSRenderSystem::IEnum::EOperationType_TriangleList);
			sub_entity->setRenderable(true);
			sub_entity->setAmbientModel(NSRenderSystem::IEnum::EMaterialAmbientModel_Constant);
			sub_entity->setDiffuseModel(NSRenderSystem::IEnum::EMaterialDiffuseModel_Lambert);
			sub_entity->getDiffuseColourUnitState()->setEnable(true);
			CFloatRGB diffuse(static_cast<Float>(mesh_info.mMaterials[i]->Diffuse.Get()[0]),static_cast<Float>(mesh_info.mMaterials[i]->Diffuse.Get()[1]),static_cast<Float>(mesh_info.mMaterials[i]->Diffuse.Get()[2]));
			sub_entity->getDiffuseColourUnitState()->setValue(CFloatRGB(diffuse*static_cast<Float>(mesh_info.mMaterials[i]->DiffuseFactor.Get())));
			if(mesh_info.mMaterials[i]->GetClassId()==fbxsdk::FbxSurfacePhong::ClassId)
			{
				auto phong=static_cast<fbxsdk::FbxSurfacePhong*>(mesh_info.mMaterials[i]);
				sub_entity->setSpecularModel(NSRenderSystem::IEnum::EMaterialSpecularModel_Phong);
				sub_entity->getSpecularColourUnitState()->setEnable(true);
				CFloatRGB specular(static_cast<Float>(phong->Specular.Get()[0]),static_cast<Float>(phong->Specular.Get()[1]),static_cast<Float>(phong->Specular.Get()[2]));
				sub_entity->getSpecularColourUnitState()->setValue(CFloatRGB(specular*static_cast<Float>(phong->SpecularFactor.Get())));
				sub_entity->getSpecularPowerUnitState()->setEnable(true);
				sub_entity->getSpecularPowerUnitState()->setValue(static_cast<Float>(phong->Shininess.Get()));
			}
			assert(mesh_info.mMaterials[i]->Diffuse.GetSrcObjectCount<fbxsdk::FbxTexture>()<=1);
			if(mesh_info.mMaterials[i]->Diffuse.GetSrcObject<fbxsdk::FbxTexture>())
			{
				if(mesh_info.mMaterials[i]->Diffuse.GetSrcObject<fbxsdk::FbxTexture>()->GetClassId()==fbxsdk::FbxFileTexture::ClassId)
				{
					auto file_tex=mesh_info.mMaterials[i]->Diffuse.GetSrcObject<fbxsdk::FbxFileTexture>();
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
				else if(mesh_info.mMaterials[i]->Diffuse.GetSrcObject<fbxsdk::FbxTexture>()->GetClassId()==fbxsdk::FbxLayeredTexture::ClassId)
				{
					assert(false);
				}
				else if(mesh_info.mMaterials[i]->Diffuse.GetSrcObject<fbxsdk::FbxTexture>()->GetClassId()==fbxsdk::FbxProceduralTexture::ClassId)
				{
					assert(false);
				}
			}

			vertex_start+=mesh_info.mVerticesByMaterial[i].size();
			index_start+=mesh_info.mIndicesByMaterial[i].size();
		}
	}
}