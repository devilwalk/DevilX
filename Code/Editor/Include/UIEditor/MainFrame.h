#pragma once
namespace NSDevilX
{
	namespace NSUIEditor
	{
		class CMainFrame
			:public TBaseObject<CMainFrame>
		{
		protected:
			NSGUISystem::IScene * mScene;
		public:
			CMainFrame();
			~CMainFrame();
			NSGUISystem::IScene * getScene()const{ return mScene; }
		};
	}
}