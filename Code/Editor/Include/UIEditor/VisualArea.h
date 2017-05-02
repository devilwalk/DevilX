#pragma once
namespace NSDevilX
{
	namespace NSUIEditor
	{
		class CVisualArea
			:public TBaseObject<CVisualArea>
		{
		protected:
			NSGUISystem::IWindow * mWindow;
		public:
			CVisualArea();
			~CVisualArea();
		};
	}
}