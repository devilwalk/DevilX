#pragma once
#include "SceneElement.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CScene;
		class CCamera
			:public TBaseObject<CCamera>
			,public CSceneElement
		{
		protected:
			CScene * const mScene;
			CPlaneBoundedVolume mPlaneBoundedVolume;
			TSharedReadData<Bool> mPlaneBoundedVolumeDirty;
		public:
			CCamera(CScene * scene);
			~CCamera();
			CScene * getScene()const
			{
				return mScene;
			}
			const CPlaneBoundedVolume & getPlaneBoundedVolume()
			{
				if(mPlaneBoundedVolumeDirty)
				{
					auto & dirty=mPlaneBoundedVolumeDirty.beginWrite();
					if(dirty)
					{
						_calculatePlaneBoundedVolume();
						dirty=false;
					}
					mPlaneBoundedVolumeDirty.endWrite();
				}
				return mPlaneBoundedVolume;
			}

		protected:
			Void _calculatePlaneBoundedVolume();
		};
	}
}