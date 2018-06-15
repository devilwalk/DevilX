#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;

NSDevilX::NSResourceSystem::CFBXResource::CFBXResource(const String & name,const String & file)
	:CFileResource(name,file)
	,mScene(nullptr)
{
	auto manager=fbxsdk::FbxManager::Create();
	mScene=fbxsdk::FbxScene::Create(manager,"");
}

NSDevilX::NSResourceSystem::CFBXResource::~CFBXResource()
{
	CFileResource::~CFileResource();
	mScene->GetFbxManager()->Destroy();
}

IEnum::EResourceType NSDevilX::NSResourceSystem::CFBXResource::getType() const
{
	return IEnum::EResourceType_FBX;
}

Boolean NSDevilX::NSResourceSystem::CFBXResource::_loadImpMT()
{
	auto importer=fbxsdk::FbxImporter::Create(mScene->GetFbxManager(),"");
	if(!importer->Initialize(getFileName().c_str()))
	{
#ifdef _MSC_VER
		OutputDebugStringA("\r\n");
		OutputDebugStringA(importer->GetStatus().GetErrorString());
		OutputDebugStringA("\r\n");
#endif
	}
	importer->Import(mScene);
	importer->Destroy();
	fbxsdk::FbxGeometryConverter converter(mScene->GetFbxManager());
	converter.RemoveBadPolygonsFromMeshes(mScene);
	converter.SplitMeshesPerMaterial(mScene,true);
	converter.Triangulate(mScene,true);
	//fbxsdk::FbxAxisSystem::DirectX.ConvertScene(mScene);
	return true;
}
