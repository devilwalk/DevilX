#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindow;
		class IControl
		{
		protected:
			virtual ~IControl(){}
		public:
			virtual NSUISystem::IElement * queryInterface_IElement()const=0;
			virtual IWindow * getParentWindow()const=0;
		};
	}
}