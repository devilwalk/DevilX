#pragma once
#include "Resource.h"
#include "RenderCommandList.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CFactory
		{
		public:
			CFactory();
			virtual ~CFactory(){ }
			virtual CBuffer * createBuffer()=0;
			virtual CShader * createShader()=0;
			virtual CProgram * createProgram()=0;
			virtual CRenderCommandList * createRenderCommandList()=0;
			virtual Void destroy(CResource * res)=0;
			virtual Void destroy(CRenderCommandList * commandList)=0;
		};
	}
}