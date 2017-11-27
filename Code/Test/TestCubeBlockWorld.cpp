#include "Common.h"
#include "InputSystem/IInputSystemInterface.h"
#include "PhysicalSystem/IPhysicalSystemInterface.h"
#include "RenderSystem/IRenderSystemInterface.h"
#include "NetWorkSystem/INetworkSystemInterface.h"
#include "CubeBlockSystem/ICubeBlockSystemInterface.h"
#include "CubeBlockWorld/ICubeBlockWorldInterface.h"
#pragma comment(lib,"RenderSystem_D3D11.lib")

using namespace NSDevilX;

namespace NSDevilX
{
	namespace NSInputSystem
	{
		class CMouseListener
			:public IMouseListener
		{
		public:
			Bool mRecord;
			CInt3 mAxisOffsets;
		public:
			CMouseListener()
				:mRecord(False)
			{}
			~CMouseListener()
			{}

			void frameMove()
			{
				mAxisOffsets=CInt3::sZero;
			}
			// 通过 IMouseListener 继承
			virtual Void addFrameData(IMouse * mouse,IMouseFrameData * data) override
			{
				switch(data->getEvent())
				{
				case IEnum::EMouseEventType_ButtonDown:
					if(data->getButtonState(IEnum::EMouseButtonType_Right)==IEnum::EButtonState_Pressed)
						mRecord=True;
					break;
				case IEnum::EMouseEventType_ButtonUp:
					if(data->getButtonState(IEnum::EMouseButtonType_Right)==IEnum::EButtonState_Released)
						mRecord=False;
					break;
				case IEnum::EMouseEventType_Move:
					if(mRecord)
						mAxisOffsets+=CInt3(data->getAxisXOffset(),data->getAxisYOffset(),data->getWheelOffset());
					break;
				}
			}
		};
		class CKeyboardListener
			:public IKeyboardListener
		{
		public:
			CKeyboardListener()
			{}
			~CKeyboardListener()
			{}
			void frameMove()
			{
			}

			// 通过 IKeyboardListener 继承
			virtual Void addFrameData(IKeyboard * keyboard,IKeyboardFrameData * data) override
			{
				return Void();
			}
		};
	}
}

Void main()
{
	UInt32 window_size[]={800,600,400,200};
	UInt32 current_window_size_index=0;
	CWindow window;
	window.setSize(CUInt2(window_size[current_window_size_index],window_size[current_window_size_index]));
	MSG msg={0};
	auto render_scene=NSRenderSystem::getSystem()->createScene("Test",NSRenderSystem::IEnum::ESceneManagerAlgorithm_Simple);
	render_scene->setAmbientColour(CFloatRGBA::sRed);
	auto render_camera=render_scene->createCamera("Test");
	render_camera->setNearClipPlane(1.0f);
	render_camera->setFarClipPlane(1000.0f);
	render_camera->setProjectionType(NSRenderSystem::IEnum::EProjectionType_Perspective);
	render_camera->queryInterface_IPerspectiveProperty()->setAspectRatio(1.0f);
	render_camera->queryInterface_IPerspectiveProperty()->setFov(CDegree(45.0f));
	auto render_direction_light=render_scene->createLight("Test_Direction",NSRenderSystem::IEnum::ELightType_Directional);
	auto * render_window=NSRenderSystem::getSystem()->createWindow(&window);
	auto render_viewport=render_window->queryInterface_IRenderTarget()->createViewport("Test");
	render_viewport->setCamera(render_camera);
	render_viewport->setClearColour(CFloatRGBA::sBlack);

	auto block_terrain_gen=NSCubeBlockWorld::getWorld()->getTerrainGenerator("Simple");
	auto block_scene_manager=NSCubeBlockWorld::getWorld()->createSceneManager("Test",block_terrain_gen,render_scene);
	block_scene_manager->setRange(CRange3I(CInt3(INT_MIN,INT_MIN,INT_MIN),CInt3(INT_MAX,0,INT_MAX)));
	auto block_loader=block_scene_manager->createLoader("Test");
	block_loader->setChunkRange(CInt3(1,1,1));

	CTransform3DNode camera_node;
	camera_node.setPosition(CFloat3(0,1.0f,0));

	CTimer timer;
	auto yaw=0.0f;
	auto pitch=0.0f;
	auto mouse=NSInputSystem::getSystem()->getVirtualDeviceManager()->createMouse("Mouse",NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDevice(0));
	auto mouse_listener=DEVILX_NEW NSInputSystem::CMouseListener();
	mouse->setListener(mouse_listener);
	auto keyboard=NSInputSystem::getSystem()->getVirtualDeviceManager()->createKeyboard("Keyboard",NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDevice(1));
	auto keyboard_listener=DEVILX_NEW NSInputSystem::CKeyboardListener();
	keyboard->setListener(keyboard_listener);
	while(keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_ESCAPE)!=NSInputSystem::IEnum::EButtonState_Pressed)
	{
		mouse_listener->frameMove();
		keyboard_listener->frameMove();

		CInt2 cursor_pos=window.getCursorPosition();
		auto delta_time=timer.getInMillisecond();
		NSInputSystem::getSystem()->update();

		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_W))
			camera_node.setPosition(camera_node.getPosition()+camera_node.getDirection()*static_cast<Float>(delta_time)*0.001f*10);
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_S))
			camera_node.setPosition(camera_node.getPosition()-camera_node.getDirection()*static_cast<Float>(delta_time)*0.001f*10);
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_A))
			camera_node.setPosition(camera_node.getPosition()-camera_node.getRight()*static_cast<Float>(delta_time)*0.001f*10);
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_D))
			camera_node.setPosition(camera_node.getPosition()+camera_node.getRight()*static_cast<Float>(delta_time)*0.001f*10);
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_SPACE))
		{
			++current_window_size_index;
			current_window_size_index=current_window_size_index%(sizeof(window_size)/sizeof(UInt32));
			window.setSize(CUInt2(window_size[current_window_size_index],window_size[current_window_size_index]));
		}
		yaw+=static_cast<Float>(mouse_listener->mAxisOffsets.x)*static_cast<Float>(delta_time)*0.001f*10;
		pitch+=static_cast<Float>(mouse_listener->mAxisOffsets.y)*static_cast<Float>(delta_time)*0.001f*10;
		pitch=std::max<Float>(pitch,-90.0f);
		pitch=std::min<Float>(pitch,90.0f);
		camera_node.setRotation(yaw,0,pitch);

		render_camera->queryInterface_ISceneElement()->getTransformer()->setPosition(camera_node.getDerivedPosition());
		render_camera->queryInterface_ISceneElement()->getTransformer()->setOrientation(camera_node.getDerivedOrientation());
		block_loader->setBlockPosition(CInt3(camera_node.getDerivedPosition())-CInt3::sUnitY*2);
		NSCubeBlockWorld::getWorld()->update();
		NSRenderSystem::getSystem()->update();

		if(PeekMessage(&msg,static_cast<HWND>(window.getHandle()),0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	NSCubeBlockWorld::getWorld()->shutdown();
	NSInputSystem::getSystem()->shutdown();
	NSRenderSystem::getSystem()->shutdown();
	DEVILX_TRACK_SHUTDOWN;
}