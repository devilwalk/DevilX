#pragma once
#include "IEventWindowImp.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IEventSceneImp
			:public IEventScene
			,public TBaseObject<IEventSceneImp>
			,public TMessageReceiver<IElementImp>
		{
		protected:
			const String mName;
			TNamedResourcePtrMap(IEventWindowImp) mWindows;
			TMap(Int32,TSet(IEventWindowImp*)) mOrderedWindows;
		public:
			IEventSceneImp(const String & name);
			~IEventSceneImp();

			// ͨ�� IEventScene �̳�
			virtual const String & getName() const override;
			virtual IEventWindow * createWindow(const String & name) override;
			virtual IEventWindow * getWindow(const String & name) const override;
			virtual Void destroyWindow(IEventWindow * window) override;
			virtual Boolean route(IEvent * e) override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(IElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}