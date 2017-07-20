#pragma once
#include "D3D11Pass.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CEntityTechnique;
			class CEntityPass
				:public CPass
				,public TMessageReceiver<ISubEntityImp>
				,public TMessageReceiver<IGeometryImp>
				,public TMessageReceiver<ITextureUnitStateImp>
			{
			protected:
				CEntityTechnique * const mTechnique;
			public:
				CEntityPass(CEntityTechnique * technique);
				virtual ~CEntityPass();
				CEntityTechnique * getTechnique()const
				{
					return mTechnique;
				}
			};
		}
	}
}