#pragma once
namespace NSDevilX
{
	namespace NSApplication
	{
		class IApplicationImp
			:public IApplication
			,public TBaseObject<IApplicationImp>
			,public TSingletonEx<IApplicationImp>
		{
		protected:
			CWindow * mWindow;
			NSRenderSystem::IWindow * mRenderWindow;
		public:
			IApplicationImp();
			~IApplicationImp();

			// Í¨¹ý IApplication ¼Ì³Ð
			virtual CWindow * getWindow() const override;
			virtual Void run() override;
			virtual Void shutdown() override;
		};
	}
}