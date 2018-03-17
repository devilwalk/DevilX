#pragma once
#include "IResourceImp.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class CFBXProcesser
			:public TBaseObject<CFBXProcesser>
		{
		public:
			struct SVertex
				:public TBaseObject<SVertex>
			{
				struct SSkinInfo
				{
					Float mWeight;
					fbxsdk::FbxCluster * mCluster;
					Boolean operator==(const SSkinInfo & info)const
					{
						return (mWeight==info.mWeight)&&(mCluster==info.mCluster);
					}
				};
				fbxsdk::FbxVector4 mPosition;
				fbxsdk::FbxVector4 mNormal;
				fbxsdk::FbxVector4 mTangent;
				fbxsdk::FbxVector2 mUV0;
				fbxsdk::FbxVector2 mUV1;
				TVector<SSkinInfo> mSkinInfos;
				fbxsdk::FbxSurfaceLambert * mMaterial;
				Boolean operator==(const SVertex & vertex)const
				{
					auto ret=(mPosition==vertex.mPosition)&&
						(mNormal==vertex.mNormal)&&
						(mTangent==vertex.mTangent)&&
						(mUV0==vertex.mUV0)&&
						(mUV1==vertex.mUV1)&&
						(mSkinInfos.size()==vertex.mSkinInfos.size())&&
						(mMaterial==vertex.mMaterial);
					if(ret)
					{
						for(size_t i=0,count=mSkinInfos.size();i<count;++i)
						{
							ret&=(mSkinInfos[i]==vertex.mSkinInfos[i]);
						}
					}
					return ret;
				}
			};
		protected:
			IResourceImp*const mResource;
			TVector<SVertex> mVertices;
			TVector<fbxsdk::FbxCluster*> mClusters;
			TVector<fbxsdk::FbxSurfaceLambert*> mMaterials;
		public:
			CFBXProcesser(IResourceImp * res);
			~CFBXProcesser();

			// Í¨¹ý CGeometryProvider ¼Ì³Ð
			Void process(NSRenderSystem::IEntity * entity);
		};
	}
}