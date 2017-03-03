#pragma once
#include "Actor.h"
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CScene
			:public TBaseObject<CScene>
			,public NSNetworkSystem::ISystemListener
		{
		protected:
			TResourcePtrList<CActor> mActors;
		public:
			CScene();
			~CScene();

			// ͨ�� ISystemListener �̳�
			virtual Void onSearch(String destIP,UInt16 port) override;
			virtual Void onConnect(String destIP,UInt16 port) override;
			virtual Void onDeconnect(NSNetworkSystem::ILink * link) override;
		};
	}
}