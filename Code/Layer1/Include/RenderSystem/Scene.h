#pragma once
#include "SceneManager.h"
#include "Camera.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CScene
		{
		protected:
			CSceneManager * mSceneManager;
			TRefResourcePtrSet(CCamera) mCameras;
		public:
			CScene();
			~CScene();
			Void setSceneManager(CSceneManager * sceneManager)
			{
				mSceneManager=sceneManager;
			}
			CSceneManager * getSceneManager()const
			{
				return mSceneManager;
			}
			CCamera * createCamera();
			Void destroyCamera(CCamera * cam);
		};
	}
}