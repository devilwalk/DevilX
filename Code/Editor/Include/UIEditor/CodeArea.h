#pragma once
namespace NSDevilX
{
	namespace NSUIEditor
	{
		class CCodeArea
			:public TBaseObject<CCodeArea>
		{
		protected:
			NSGUISystem::IWindow * mWindow;
		public:
			CCodeArea();
			~CCodeArea();
		};
	}
}