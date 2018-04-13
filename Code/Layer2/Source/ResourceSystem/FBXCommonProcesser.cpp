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
				mMeshes.push_back(static_cast<fbxsdk::FbxMesh*>(node->GetNodeAttributeByIndex(attr_index)));
				break;
			}
		}
	}
	return true;
}
