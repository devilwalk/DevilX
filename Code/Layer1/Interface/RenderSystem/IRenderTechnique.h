#pragma once
#include "IRenderPass.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IMaterial;
		class ITechnique
		{
		protected:
			virtual ~ITechnique()
			{
			}
		public:
			virtual IMaterial * getMaterial()const=0;
			virtual const String & getName()const=0;
			virtual Void setSchemeName(const String & name)=0;
			virtual const String getSchemeName()const=0;
			virtual IPass * createPass()=0;
			virtual IPass * getPass(UInt32 index)const=0;
			virtual Void destroyPass(IPass * pass)=0;
		};
	}
}