#pragma once
#include "IResourceImp.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class CFBXResource
			:public CFileResource
			,public TBaseObject<CFBXResource>
		{
		protected:
			fbxsdk::FbxScene * mScene;
		public:
			CFBXResource(const String & name,const String & file);
			~CFBXResource();
			fbxsdk::FbxScene * getScene()const{ return mScene; }
			virtual IEnum::EResourceType getType() const override;
			// Í¨¹ý CFileResource ¼Ì³Ð
			virtual Boolean _loadImpMT() override;
		};
	}
}