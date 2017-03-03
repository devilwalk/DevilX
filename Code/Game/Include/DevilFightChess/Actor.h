#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CScene;
		class CActor
			:public TBaseObject<CActor>
		{
		protected:
			CScene * const mScene;
			NSNetworkSystem::ILink * const mLink;
		public:
			CActor(CScene * scene,NSNetworkSystem::ILink * link);
			~CActor();
			CScene * getScene()const
			{
				return mScene;
			}
			NSNetworkSystem::ILink * getLink()const
			{
				return mLink;
			}
		};
	}
}