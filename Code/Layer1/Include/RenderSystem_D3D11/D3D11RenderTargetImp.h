#pragma once
#include "D3D11BaseObject.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CColourSurfaceImp
				:public TCOMInternalObject<ID3D11RenderTargetView>
				,public CColourSurface
				,public TBaseObject<CColourSurfaceImp>
			{
			protected:
			public:
				CColourSurfaceImp();
				~CColourSurfaceImp();
			};
			class CDepthStencilSurfaceImp
				:public TBaseObject<CDepthStencilSurfaceImp>
				,public TCOMInternalObject<ID3D11DepthStencilView>
				,public CDepthStencilSurface
			{
			protected:
			public:
				CDepthStencilSurfaceImp();
				~CDepthStencilSurfaceImp();
			};
		}
	}
}