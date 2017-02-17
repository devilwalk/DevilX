#pragma once
#include "IResourceManagerImp.h"
#include "ISceneImp.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class ISystemImp
			:public ISystem
			,public TBaseObject<ISystemImp>
			,public TSingleton<ISystemImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_Destruction,
				EMessage_BeginSceneCreate,
				EMessage_EndSceneCreate,
				EMessage_BeginSceneDestroy,
				EMessage_EndSceneDestroy
			};
		protected:
			Bool mExit;
			IResourceManagerImp * mResourceManager;
			TNamedResourcePtrMap<ISceneImp> mScenes;
		public:
			ISystemImp();
			~ISystemImp();
			Bool isExit()const
			{
				return mExit;
			}
			// Inherited via ISystem
			virtual IResourceManager * queryInterface_IResourceManager() const override;
			virtual Void shutdown() override;
			virtual Void update() override;
			virtual IScene * createScene(const String & name) override;
			virtual Void destroyScene(IScene * scene) override;
			virtual IScene * getScene(const String & name) const override;
		};
	}
}