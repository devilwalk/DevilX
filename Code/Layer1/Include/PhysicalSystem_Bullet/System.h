#pragma once
#include "ResourceManager.h"
#include "Scene.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		namespace NSBullet
		{
			class CSystem
				:public TBaseObject<CSystem>
				,public TSingleton<CSystem>
				,public CMessageNotifier
				,public TMessageReceiver<ISystemImp>
			{
			public:
				enum EMessage
				{
					EMessage_BeginUpdate,
					EMessage_EndUpdate
				};
			protected:
				CResourceManager * mResourceManager;
				TResourcePtrMap<ISceneImp*,CScene> mScenes;
				TResourcePtrMap<ConstVoidPtr,Void> mInstanceByInterfaceImps;
				TResourcePtrMap<ConstVoidPtr,Void> mInstanceByInternals;
			public:
				CSystem();
				~CSystem();
				CResourceManager * getResourceManager()const
				{
					return mResourceManager;
				}
				Void update();
				VoidPtr getInstanceByInterfaceImp(ConstVoidPtr interfaceImp)const
				{
					return mInstanceByInterfaceImps.get(interfaceImp);
				}
				Boolean hasInstanceByInterfaceImp(ConstVoidPtr interfaceImp)const
				{
					return mInstanceByInterfaceImps.has(interfaceImp);
				}
				Void addInstanceByInterfaceImp(ConstVoidPtr interfaceImp,VoidPtr instance)
				{
					mInstanceByInterfaceImps.add(interfaceImp,instance);
				}
				Void removeInstanceByInterfaceImp(ConstVoidPtr interfaceImp)
				{
					mInstanceByInterfaceImps.erase(interfaceImp);
				}
				VoidPtr getInstanceByInternal(ConstVoidPtr interfaceImp)const
				{
					return mInstanceByInternals.get(interfaceImp);
				}
				Boolean hasInstanceByInternal(ConstVoidPtr interfaceImp)const
				{
					return mInstanceByInternals.has(interfaceImp);
				}
				Void addInstanceByInternal(ConstVoidPtr interfaceImp,VoidPtr instance)
				{
					mInstanceByInternals.add(interfaceImp,instance);
				}
				Void removeInstanceByInternal(ConstVoidPtr interfaceImp)
				{
					mInstanceByInternals.erase(interfaceImp);
				}
				// Inherited via TInterfaceObject
				virtual void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}