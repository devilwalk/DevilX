#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CEvent
			:public NSUISystem::IEvent
		{
		public:
			enum EType
			{
				EType_MouseMove
			};
		protected:
			EType const mType;
			NSUISystem::IElement * mLayer;
		public:
			CEvent(EType type)
				:mType(type)
			{
				mLayer=NSUISystem::getSystem()->createLayer("Event/"+CStringConverter::toString(getType())+"/"+CStringConverter::toString(this));
			}
			~CEvent()
			{
				NSUISystem::getSystem()->destroyLayer(queryInterface_IElement());
			}
			virtual NSUISystem::IElement * queryInterface_IElement() const override
			{
				return mLayer;
			}
			virtual UInt32 getType() const override
			{
				return mType;
			}
		};
	}
}