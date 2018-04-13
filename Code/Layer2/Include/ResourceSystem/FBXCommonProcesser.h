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
		protected:
			CFBXProcesser*mFBXProcesser;
			TVector<fbxsdk::FbxNode*> mNodes;
			TVector<fbxsdk::FbxMesh*> mMeshes;
			TVector<fbxsdk::FbxCluster*> mClusters;
		public:
			CFBXCommonProcesser(CFBXProcesser * processer);
			~CFBXCommonProcesser();
			const decltype(mNodes) & getNodes()const{ return mNodes; }
			const decltype(mMeshes) & getMeshes()const{ return mMeshes; }
		protected:
			Void _getNodes(fbxsdk::FbxNode * node);
			// Í¨¹ý CResource ¼Ì³Ð
			virtual Boolean _loadImpMT() override;
		};
	}
}