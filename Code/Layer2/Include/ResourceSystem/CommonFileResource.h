#pragma once
#include "IResourceImp.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class CCommonFileResource
			:public CFileResource
			,public TBaseObject<CCommonFileResource>
		{
		protected:
			CFileStream mFileStream;
			CMemoryStream mMemoryStream;
		public:
			CCommonFileResource(const String & name,const String & filename);
			~CCommonFileResource();
			const CFileStream & getFileStream()const{ return mFileStream; }
			const CMemoryStream & getMemoryStream()
			{
				if(!mMemoryStream.getSize())
					mMemoryStream.load(&mFileStream);
				return mMemoryStream;
			}

			// Í¨¹ý CFileResource ¼Ì³Ð
			virtual IEnum::EResourceType getType() const override;
			virtual Boolean _loadImpMT() override;
		};
	}
}