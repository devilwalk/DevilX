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
			virtual const String & getName() const override;
			virtual Void setPosition(const CFloat2 & position) override;
			virtual const CFloat2 & getPosition() const override;
			virtual Void setSize(const CFloat2 & size) override;
			virtual const CFloat2 & getSize() const override;
			virtual IWindow * getParentWindow() const override;
		};
	}
}