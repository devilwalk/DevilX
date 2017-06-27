#pragma once
#include "IResourceManagerImp.h"
#include "IWindowImp.h"
#include "IRenderableSurfaceImp.h"
#include "ISceneImp.h"
#include "DefnitionShaderCodeFunction.h"
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
				EMessage_EndSceneDestroy,
				EMessage_BeginRenderableSurfaceCreate,
				EMessage_EndRenderableSurfaceCreate,
				EMessage_BeginRenderableSurfaceDestroy,
				EMessage_EndRenderableSurfaceDestroy
			};
		protected:
			Bool mExit;
			UInt32 mFrameIndex;
			Float mFrameTimeInSecond;
			CDefinitionShader * mDefinitionShader;
			IResourceManagerImp * mResourceManager;
			TResourcePtrMap<CWindow*,IWindowImp> mWindows;
			TNamedResourcePtrMap<IRenderableSurfaceImp> mRenderableSurfaces;
			TNamedResourcePtrMap<ISceneImp> mScenes;
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
			CDefinitionShader * getDefinitionShader()const
			{
				return mDefinitionShader;
			}
			// Inherited via ISystem
			virtual Void shutdown() override;
			virtual IResourceManager * queryInterface_IResourceManager() const override;
			virtual Void update() override;
			virtual IWindow * createWindow(CWindow * window) override;
			virtual Void destroyWindow(IWindow * window) override;
			virtual IWindow * getWindow(CWindow * window) const override;
			virtual IRenderableSurface * createRenderableSurface(const String & name) override;
			virtual Void destroyRenderableSurface(IRenderableSurface * surface) override;
			virtual IRenderableSurface * getRenderableSurface(const String & name) const override;
			virtual IScene * createScene(const String & name,IEnum::ESceneManagerAlgorithm algorithm) override;
			virtual Void destroyScene(IScene * scene) override;
			virtual IScene * getScene(const String & name) const override;
		};
	}
}