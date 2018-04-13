#pragma once
#include "IResourceImp.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class CImageResource
			:public CFileResource
			,public TBaseObject<CImageResource>
		{
		protected:
			CImage * mImage;
		public:
			CImageResource(const String & name,const String & file);
			virtual ~CImageResource();
			CImage * getImage()const{ return mImage; }
			virtual IEnum::EResourceType getType() const override;
		protected:
			virtual Boolean _loadImpMT() override;

		};
	}
}