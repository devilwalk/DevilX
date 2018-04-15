#pragma once
#include "FBXResource.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class CFBXProcesser;
		class CFBXCommonProcesser
			:public TBaseObject<CFBXCommonProcesser>
			,public CResource
		{
		public:
			struct SBone
				:public TBaseObject<SBone>
			{
				fbxsdk::FbxCluster * const mCluster;
				SBone(fbxsdk::FbxCluster * cluster)
					:mCluster(cluster)
				{}
				Boolean isMatch(fbxsdk::FbxCluster * cluster)const
				{
					fbxsdk::FbxAMatrix mat1,mat2;
					return ((mCluster->GetLink()==cluster->GetLink())
						&&(mCluster->GetTransformLinkMatrix(mat1)==cluster->GetTransformLinkMatrix(mat2))
						&&(mCluster->GetTransformMatrix(mat1)==cluster->GetTransformMatrix(mat2)));
				}
			};
		protected:
			CFBXProcesser*mFBXProcesser;
			TVector<fbxsdk::FbxNode*> mNodes;
			TVector<fbxsdk::FbxMesh*> mMeshes;
			TVector<SBone> mBones;
		public:
			CFBXCommonProcesser(CFBXProcesser * processer);
			~CFBXCommonProcesser();
			const decltype(mNodes) & getNodes()const{ return mNodes; }
			const decltype(mMeshes) & getMeshes()const{ return mMeshes; }
			const decltype(mBones) & getBones()const{ return mBones; }
		protected:
			Void _getNodes(fbxsdk::FbxNode * node);
			// Í¨¹ý CResource ¼Ì³Ð
			virtual Boolean _loadImpMT() override;
		};
	}
}