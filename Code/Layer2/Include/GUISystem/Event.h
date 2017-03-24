#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CEvent
			:public NSUISystem::IEvent
		{
		protected:
			const UInt32 mType;
			NSUISystem::IElement * mLayer;
		public:
			CEvent(UInt32 type);
			virtual ~CEvent();

			// ͨ�� IEvent �̳�
			virtual NSUISystem::IElement * queryInterface_IElement() const override;
			virtual UInt32 getType() const override;
		};
	}
}