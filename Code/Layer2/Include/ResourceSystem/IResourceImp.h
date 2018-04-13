#pragma once
#include "Resource.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class ISystemImp;
		class IResourceImp
			:public IResource
			,public CResource
		{
		protected:
			const String mName;
		public:
			IResourceImp(const String & name);
			virtual ~IResourceImp();
			// Í¨¹ý IResource ¼Ì³Ð
			virtual const String & getName() const override;
			virtual Void load(ILoadCallback * callback,Bool sync) override;
			virtual Boolean isLoaded() const override;
		};
		class CFileResource
			:public IResourceImp
		{
		protected:
			const String mFile;
		public:
			CFileResource(const String & name,const String & file);
			virtual ~CFileResource();
			const String & getFileName()const{ return mFile; }
		};
	}
}