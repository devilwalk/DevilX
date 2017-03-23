#pragma once
#include "Control.h"
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindowImp;
		class IControlImp
			:public IControl
			,public TBaseObject<IControlImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction
			};
		protected:
			IWindowImp * const mParentWindow;
			CControl * const mControl;
		public:
			IControlImp(CControl * control,IWindowImp * parentWindow);
			~IControlImp();
			CControl * getControl()const
			{
				return mControl;
			}
			// Í¨¹ý IControl ¼Ì³Ð
			virtual NSUISystem::IElement * queryInterface_IElement() const override;
			virtual IWindow * getParentWindow() const override;
		};
	}
}