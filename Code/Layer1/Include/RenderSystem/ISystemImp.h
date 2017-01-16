#pragma once
#include "IResourceManagerImp.h"
#include "IRenderTargetImp.h"
#include "ISceneImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISystemImp
			:public ISystem
			,public TSingleton<ISystemImp>
			,public TBaseObject<ISystemImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Update,
				EMessage_Destruction,
				EMessage_BeginWindowCreate,
				EMessage_EndWindowCreate,
				EMessage_BeginWindowDestroy,
				EMessage_EndWindowDestroy,
				EMessage_BeginSceneCreate,
				EMessage_EndSceneCreate,
				EMessage_BeginSceneDestroy,
				EMessage_EndSceneDestroy
			};
		protected:
			Bool mExit;
			UInt32 mFrameIndex;
			Float mFrameTimeInSecond;
			IResourceManagerImp * mResourceManager;
			TResourcePtrContainer<VoidPtr,IWindowImp> mWindows;
			TNamedResourcePtrContainer<ISceneImp> mScenes;
		public:
			ISystemImp();
			~ISystemImp();
			decltype(mExit) isExit()const
			{
				return mExit;
			}
			decltype(mFrameIndex) getFrameIndex()const
			{
				return mFrameIndex;
			}
			decltype(mFrameTimeInSecond) getFrameTimeInSecond()const
			{
				return mFrameTimeInSecond;
			}
			// Inherited via ISystem
			virtual Void shutdown() override;
			virtual IResourceManager * queryInterface_IResourceManager() const override;
			virtual Void update() override;
			virtual IWindow * createWindow(VoidPtr windowHandle) override;
			virtual Void destroyWindow(IWindow * window) override;
			virtual IWindow * getWindow(VoidPtr windowHandle) const override;
			virtual IScene * createScene(const String & name,IEnum::ESceneManagerAlgorithm algorithm) override;
			virtual Void destroyScene(IScene * scene) override;
			virtual IScene * getScene(const String & name) const override;
		};
	}
}