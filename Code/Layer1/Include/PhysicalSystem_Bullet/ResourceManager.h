#pragma once
#include "Mesh.h"
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		namespace NSBullet
		{
			class CResourceManager
				:public TBaseObject<CResourceManager>
				,public TMessageReceiver<IResourceManagerImp>
			{
			protected:
				TResourcePtrMap(IMeshImp*,CMesh) mMeshes;
			public:
				CResourceManager();
				~CResourceManager();
				CMesh * getMesh(IMeshImp * interfaceImp)const
				{
					return mMeshes.get(interfaceImp);
				}
				// Inherited via TMessageReceiver
				virtual void onMessage(IResourceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			};
		}
	}
}