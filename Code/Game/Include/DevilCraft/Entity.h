#pragma once
namespace NSDevilX
{
	namespace NSDevilCraft
	{
		class CScene;
		class CEntity
		{
		protected:
			const String mName;
			CScene * const mScene;
			NSRenderSystem::IEntity * mRenderEntity;
			NSPhysicalSystem::IEntity * mPhysicalEntity;
		public:
			CEntity(const String & name,CScene * scene);
			virtual ~CEntity();
		};
	}
}