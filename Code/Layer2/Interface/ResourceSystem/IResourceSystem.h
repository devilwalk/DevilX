#pragma once
#include "IResource.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class ISystem
		{
		protected:
			virtual ~ISystem(){}
		public:
			virtual IResource * createResource(const String & name,const String & fileName)=0;
			virtual IResource * getResource(const String & name)const=0;
			virtual Void destroyResource(IResource * res)=0;
		};
		ISystem * getSystem();
	}
}