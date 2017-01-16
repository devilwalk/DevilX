#pragma once
#include "Common.h"
#include "RenderSystem/IRenderSystemInterface.h"
#include "CubeBlockSystem/ICubeBlockSystemInterface.h"
#include "CubeBlockWorld/ICubeBlockWorldInterface.h"
#include "Base.h"
#include "Simple.h"
extern"C" __declspec(dllexport) NSDevilX::Boolean install(NSDevilX::NSCubeBlockWorld::IWorld * world,NSDevilX::NSCubeBlockSystem::ISystem * system);
extern"C" __declspec(dllexport) NSDevilX::Void dllUnload();
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class CModule
			:public TSingleton<CModule>
			,public TBaseObject<CModule>
		{
		protected:
			IWorld * const mWorld;
			NSCubeBlockSystem::ISystem * const mSystem;
		public:
			CModule(IWorld * world,NSCubeBlockSystem::ISystem * system);
			~CModule();
			IWorld * getWorld()const
			{
				return mWorld;
			}
			NSCubeBlockSystem::ISystem * getSystem()const
			{
				return mSystem;
			}
		};
	}
}