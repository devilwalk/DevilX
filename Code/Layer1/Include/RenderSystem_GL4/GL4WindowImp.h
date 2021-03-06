#pragma once
#include "GL4RenderTargetImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CWindowImp
				:public TBaseObject<CWindowImp>
				,public TInterfaceObject<IWindowImp>
				,public CRenderTargetImp
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_BeginResize,
					EMessage_EndResize
				};
			protected:
				VoidPtr mDC;
			public:
				CWindowImp(IWindowImp * interfaceImp);
				~CWindowImp();
				decltype(mDC) getDC()const
				{
					return mDC;
				}
				virtual Void prepare() override;
				virtual Void render() override;
			protected:
				Void _resize();
				// Inherited via TInterfaceObject
				virtual Void onMessage(IWindowImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}