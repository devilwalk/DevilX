#pragma once
#include "FBXResource.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class CFBXProcesser;
		class CFBXRenderProcesser
			:public TBaseObject<CFBXRenderProcesser>
			,public CResource
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
				SVertex()
					:mPosition(0)
					,mNormal(0)
					,mTangent(0)
					,mUV0(-1,-1)
					,mUV1(-1,-1)
				{}
				Boolean operator==(const SVertex & vertex)const
				{
					auto ret=((mPosition==vertex.mPosition)&&
						(mNormal==vertex.mNormal)&&
						(mTangent==vertex.mTangent)&&
						(mUV0==vertex.mUV0)&&
						(mUV1==vertex.mUV1)&&
						(mSkinInfos.size()==vertex.mSkinInfos.size()));
					if(ret)
					{
						for(size_t i=0,count=mSkinInfos.size();i<count;++i)
						{
							ret&=(mSkinInfos[i]==vertex.mSkinInfos[i]);
						}
					}
					return ret;
				}
				Boolean hasNormal()const
				{
					return mNormal!=fbxsdk::FbxVector4(0);
				}
				Boolean hasTangent()const
				{
					return mTangent!=fbxsdk::FbxVector4(0);
				}
				Boolean hasUV0()const
				{
					return mUV0!=fbxsdk::FbxVector2(-1,-1);
				}
				Boolean hasUV1()const
				{
					return mUV1!=fbxsdk::FbxVector2(-1,-1);
				}
				Boolean hasSkin()const
				{
					return !mSkinInfos.empty();
				}
			};
			struct SMeshInfo
				:public TBaseObject<SMeshInfo>
			{
				TVector<SVertex> mVertices;
				TVector<UInt32> mIndices;
				fbxsdk::FbxSurfaceLambert * mMaterial;
			};
		protected:
			CFBXProcesser*mFBXProcesser;
			TVector<SMeshInfo> mMeshes;
		public:
			CFBXRenderProcesser(CFBXProcesser * processer);
			~CFBXRenderProcesser();
			const decltype(mMeshes) & getMeshes()const{ return mMeshes; }
			// Í¨¹ý CResource ¼Ì³Ð
			virtual Boolean _loadImpMT() override;
		};
	}
}