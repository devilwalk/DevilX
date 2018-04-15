#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::CFBXCommonProcesser::CFBXCommonProcesser(CFBXProcesser * processer)
	:mFBXProcesser(processer)
{
}

NSDevilX::NSResourceSystem::CFBXCommonProcesser::~CFBXCommonProcesser()
{
	CResource::~CResource();
}

Void NSDevilX::NSResourceSystem::CFBXCommonProcesser::_getNodes(fbxsdk::FbxNode * node)
{
	if(node->GetVisibility())
		mNodes.push_back(node);
	for(auto i=0;i<node->GetChildCount();++i)
	{
		_getNodes(node->GetChild(i));
	}
}

Boolean NSDevilX::NSResourceSystem::CFBXCommonProcesser::_loadImpMT()
{
	_getNodes(mFBXProcesser->getFBXResource()->getScene()->GetRootNode());
	for(auto node:mNodes)
	{
		for(auto attr_index=0;attr_index<node->GetNodeAttributeCount();++attr_index)
		{
			switch(node->GetNodeAttributeByIndex(attr_index)->GetAttributeType())
			{
			case fbxsdk::FbxNodeAttribute::eMesh:
			{
				auto mesh=static_cast<fbxsdk::FbxMesh*>(node->GetNodeAttributeByIndex(attr_index));
				mMeshes.push_back(mesh);
				assert(mesh->GetDeformerCount()<=1);
				if(mesh->GetDeformerCount())
				{
					for(auto deformer_index=0;deformer_index<mesh->GetDeformerCount();++deformer_index)
					{
						if(mesh->GetDeformer(deformer_index)->GetDeformerType()!=fbxsdk::FbxDeformer::eSkin)
							continue;
						auto skin=static_cast<fbxsdk::FbxSkin*>(mesh->GetDeformer(deformer_index));
						for(auto cluster_index=0;cluster_index<skin->GetClusterCount();cluster_index++)
						{
							auto cluster=skin->GetCluster(cluster_index);
							struct SFindIf
							{
								fbxsdk::FbxCluster * const mCluster;
								SFindIf(fbxsdk::FbxCluster * cluster)
									:mCluster(cluster)
								{}
								Boolean operator()(const SBone & bone)const
								{
									return bone.isMatch(mCluster);
								}
							};
							SFindIf find_if_func(cluster);
							if(mBones.end()==std::find_if(mBones.begin(),mBones.begin(),find_if_func))
							{
								mBones.push_back(SBone(cluster));
							}
						}
					}
				}
			}
			break;
			}
		}
	}
	return true;
}
