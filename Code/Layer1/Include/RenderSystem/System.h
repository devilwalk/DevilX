#pragma once
#include "Resource.h"
#include "RenderCommandList.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CSystem
			:public TBaseObject<CSystem>
			,public TSingletonEx<CSystem>
		{
		protected:
			CFactory * mFactory;
			TSet(CResource*) mResources;
		public:
			CSystem();
			~CSystem();
			Void setFactory(CFactory * factory)
			{
				mFactory=factory;
			}
			CBuffer * createBuffer()
			{
				auto ret=mFactory->createBuffer();
				mResources.insert(ret);
				return ret;
			}
			Void destroy(CResource * res)
			{
				mResources.erase(res);
				mFactory->destroy(res);
			}
			CRenderCommandList * createRenderCommandList();
		};
	}
}