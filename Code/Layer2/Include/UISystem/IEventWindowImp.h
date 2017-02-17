#pragma once
#include "IElementImp.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IEventWindowImp
			:public IEventWindow
			,public TBaseObject<IEventWindowImp>
		{
		public:
			struct SEventNotifier;
			struct SEventListener
				:public TMessageReceiver<SEventNotifier>
				,public TBaseObject<SEventListener>
			{
				IEventListener * mListener;
				SEventListener()
					:mListener(nullptr)
				{}
				virtual Void onMessage(SEventNotifier * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override
				{
					mListener->onEvent(static_cast<IEvent*>(data));
				}
			};
			struct SEventNotifier
				:public CMessageNotifier
				,public TBaseObject<SEventNotifier>
			{

			};
		protected:
			IElementImp * mElement;
			SEventNotifier mEventNotifier;
			TResourcePtrMap<IEventListener*,SEventListener> mEventListeners;
		public:
			IEventWindowImp(const String & name);
			virtual ~IEventWindowImp();
			Void notify(IEvent * e);
			// Í¨¹ý IEventWindow ¼Ì³Ð
			virtual IElement * queryInterface_IElement() const override;
			virtual Void registerListener(IEventListener * listener,UInt32 eventType) override;
			virtual Void unregisterListener(IEventListener * listener,UInt32 eventType) override;
		};
	}
}