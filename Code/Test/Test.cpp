// Project.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Common.h"
#include "InputSystem/IInputSystemInterface.h"
#include "PhysicalSystem/IPhysicalSystemInterface.h"
#include "RenderSystem/IRenderSystemInterface.h"
#include "NetWorkSystem/INetworkSystemInterface.h"
#include "UISystem/IUISystemInterface.h"
#include "ResourceSystem/IResourceSystemInterface.h"
#pragma comment(lib,"RenderSystem_D3D11.lib")
//#pragma comment(lib,"RenderSystem_GL4.2017.lib")
using namespace NSDevilX;
class CPhysicalQueryResultReceiver
	:public NSPhysicalSystem::IQueryResultReceiver
	,public TBaseObject<CPhysicalQueryResultReceiver>
{
public:
	// Inherited via IQueryResultReceiver
	virtual Void addHitSubEntity(NSPhysicalSystem::ISubEntity * subEntity) override
	{
		std::cout<<"HitSubEntity:"<<subEntity->getSubMesh()->getName().c_str()<<std::endl;
	}

	virtual Void addHitPoint(const CFloat3 & position,const CFloat3 & normal) override
	{
		std::cout<<"HitPosition:x:"<<position.x<<" y:"<<position.y<<" z:"<<position.z<<"\tHitNormal:x:"<<normal.x<<" y:"<<normal.y<<" z:"<<normal.z<<std::endl;
	}

};
int main()
{
	auto physical_scene=NSPhysicalSystem::getSystem()->createScene("Test");
	auto physical_geometry=NSPhysicalSystem::getSystem()->queryInterface_IResourceManager()->createGeometry("Test");
	auto physical_mesh=NSPhysicalSystem::getSystem()->queryInterface_IResourceManager()->createMesh("Test");
	auto physical_sub_mesh=physical_mesh->createSubMesh("Test");
	auto physical_entity=physical_scene->createEntity("Test");
	auto physical_ray_query=physical_scene->createQuery("TestRay",NSPhysicalSystem::IEnum::EQueryType_Ray);
	physical_entity->setMesh(physical_mesh);
	physical_mesh->setGeometry(physical_geometry);
	physical_geometry->setVertexCount(3);
	physical_geometry->setIndexCount(3);
	const CFloat3 positions[]={CFloat3(-1.0f,0,10.0f),CFloat3(0,1.0f,10.0f),CFloat3(1.0f,0,10.0f)};
	physical_geometry->setPositions(positions);
	const UInt32 indices[]={0,1,2};
	physical_geometry->setIndices(indices);
	physical_sub_mesh->setIndexCount(physical_geometry->getIndexCount());
	physical_ray_query->addResultType(NSPhysicalSystem::IEnum::EQueryResultType_HitPoint);
	physical_ray_query->addResultType(NSPhysicalSystem::IEnum::EQueryResultType_HitSubEntity);
	CPhysicalQueryResultReceiver physical_query_result_receiver;
	physical_ray_query->setResultReceiver(&physical_query_result_receiver);
	CFloat3 ray_dir=CFloat3(0.5f,0.5f,1.0f);
	ray_dir.normalize();
	physical_ray_query->queryInterface_IRayQuery()->setRay(CRay(CFloat3(0,0,-1.0f),ray_dir));

	UInt32 window_size[]={800,600,400,200};
	UInt32 current_window_size_index=0;
	CWindow window;
	window.setSize(CUInt2(window_size[current_window_size_index],window_size[current_window_size_index]));
	MSG msg={0};
	auto render_scene=NSRenderSystem::getSystem()->createScene("Test",NSRenderSystem::IEnum::ESceneManagerAlgorithm_Simple);
	render_scene->setAmbientColour(CFloatRGB(CFloatRGBA::sRed*0.1f));
	auto render_camera=render_scene->createCamera("Test");
	render_camera->setNearClipPlane(1.0f);
	render_camera->setFarClipPlane(1000.0f);
	render_camera->setProjectionType(NSRenderSystem::IEnum::EProjectionType_Perspective);
	render_camera->queryInterface_IPerspectiveProperty()->setAspectRatio(1.0f);
	render_camera->queryInterface_IPerspectiveProperty()->setFov(CDegree(45.0f));
	auto render_direction_light=render_scene->createLight("Test_Direction",NSRenderSystem::IEnum::ELightType_Directional);
	render_direction_light->getDiffuseColourUnitState()->setEnable(True);
	render_direction_light->getDiffuseColourUnitState()->setValue(CFloatRGB::sWhite);
	auto render_point_light=render_scene->createLight("Test_Point",NSRenderSystem::IEnum::ELightType_Point);
	render_point_light->queryInterface_ISceneElement()->getTransformer()->setScale(CFloat3(20.0f));
	render_point_light->queryInterface_ISceneElement()->getTransformer()->setPosition(CFloat3(0,10.0f,0));
	auto render_point_light_area=render_scene->createVisibleArea("Test_Point");
	render_point_light_area->setBoundingBox(DirectX::BoundingBox(CFloat3::sZero,CFloat3(20.0f)));
	render_point_light_area->attachObject(render_point_light->queryInterface_ISceneElement());
	auto render_spot_light=render_scene->createLight("Test_Spot",NSRenderSystem::IEnum::ELightType_Spot);
	render_spot_light->queryInterface_ISpotLightProperty()->setAngle(45);
	render_spot_light->queryInterface_ISceneElement()->getTransformer()->setScale(CFloat3(100.0f));
	render_spot_light->queryInterface_ISceneElement()->getTransformer()->setPosition(CFloat3(20.0f,10.0f,0));
	CTransform3DNode spot_light_node;
	spot_light_node.setDirection(-CFloat3::sUnitY,CFloat3::sUnitX);
	render_spot_light->queryInterface_ISceneElement()->getTransformer()->setOrientation(spot_light_node.getOrientation());
	auto render_spot_light_area=render_scene->createVisibleArea("Test_Spot");
	render_spot_light_area->setBoundingBox(DirectX::BoundingBox(CFloat3::sZero,CFloat3(100.0f)));
	render_spot_light_area->attachObject(render_spot_light->queryInterface_ISceneElement());
	auto * render_window=NSRenderSystem::getSystem()->createWindow(&window);
	auto render_viewport=render_window->queryInterface_IRenderTarget()->createViewport("Test");
	render_viewport->setCamera(render_camera);
	render_viewport->setClearColour(CFloatRGBA::sBlack);
	auto query=render_viewport->createQuery("Test");
	query->setArea(CFloat2(-1.0f),CFloat2(-1.0f));
	auto render_geometry=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry("Test");
	render_geometry->getVertexBuffer()->setCount(3);
	render_geometry->getVertexBuffer()->setPositions(positions);
	auto render_entity=render_scene->createEntity("Test");
	auto render_sub_entity=render_entity->createSubEntity("0");
	render_sub_entity->setQueriable(True);
	render_sub_entity->setGeometry(render_geometry);
	render_sub_entity->setAmbientModel(NSRenderSystem::IEnum::EMaterialAmbientModel_None);
	render_sub_entity->setDiffuseModel(NSRenderSystem::IEnum::EMaterialDiffuseModel_None);
	render_sub_entity->setSpecularModel(NSRenderSystem::IEnum::EMaterialSpecularModel_None);
	render_sub_entity->getEmissiveColourUnitState()->setEnable(True);
	render_sub_entity->getEmissiveColourUnitState()->setValue(CFloatRGBA::sWhite);
	render_sub_entity->setVisible(True);
	UInt32 query_datas[]={666,666,666};
	auto query_buffer=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createBuffer("Query");
	query_buffer->setSize(sizeof(query_datas));
	query_buffer->setDatas(query_datas);
	render_sub_entity->setQueryBuffer(query_buffer);
	render_sub_entity->queryInterface_IGeometryUsage()->setVertexCount(3);
	auto render_visible_area=render_scene->createVisibleArea("Test_Entity");
	render_visible_area->setBoundingBox(DirectX::BoundingBox(CFloat3::sZero,CFloat3(100.0f)));
	//render_visible_area->attachObject(render_entity->queryInterface_ISceneElement());

	auto fbx_res=NSResourceSystem::getSystem()->createOrRetrieveResource("Model","Resource/girlA.fbx");
	fbx_res->load(nullptr,True);
	auto render_geometry_model=NSResourceSystem::getSystem()->getRenderGeometry(fbx_res);
	auto render_entity_model=render_scene->createEntity("Model");
	render_entity_model->queryInterface_ISceneElement()->getTransformer()->setPosition(CFloat3(0,0,10.0f));
	auto render_sub_entity_model=render_entity_model->createSubEntity("0");
	render_sub_entity_model->setGeometry(render_geometry_model);
	render_sub_entity_model->setAmbientModel(NSRenderSystem::IEnum::EMaterialAmbientModel_Constant);
	render_sub_entity_model->setDiffuseModel(NSRenderSystem::IEnum::EMaterialDiffuseModel_Lambert);
	render_sub_entity_model->getDiffuseColourUnitState()->setEnable(True);
	render_sub_entity_model->getDiffuseColourUnitState()->setValue(CFloatRGB::sRed);
	render_sub_entity_model->setSpecularModel(NSRenderSystem::IEnum::EMaterialSpecularModel_None);
	render_sub_entity_model->setVisible(True);
	render_sub_entity_model->queryInterface_IGeometryUsage()->setVertexCount(render_geometry_model->getVertexBuffer()->getCount());
	render_sub_entity_model->queryInterface_IGeometryUsage()->setIndexCount(render_geometry_model->getIndexBuffer()->getCount());
	render_visible_area->attachObject(render_entity_model->queryInterface_ISceneElement());


	//auto ui_graphic_scene=NSUISystem::getSystem()->createGraphicScene(render_viewport);
	//auto ui_graphic_window_lt=ui_graphic_scene->createWindow("Test_LT");
	//ui_graphic_window_lt->queryInterface_IElement()->setPosition(CFloat2::sZero);
	//ui_graphic_window_lt->queryInterface_IElement()->setSize(CFloat2(0.25f));
	//ui_graphic_window_lt->setColour(CFloatRGBA::sRed);
	//auto ui_graphic_window_rt=ui_graphic_scene->createWindow("Test_RT");
	//ui_graphic_window_rt->queryInterface_IElement()->setPosition(CFloat2(0.25f,0.0f));
	//ui_graphic_window_rt->queryInterface_IElement()->setSize(CFloat2(0.25f));
	//ui_graphic_window_rt->setColour(CFloatRGBA::sGreen);
	//auto ui_graphic_window_lb=ui_graphic_scene->createWindow("Test_LB");
	//ui_graphic_window_lb->queryInterface_IElement()->setPosition(CFloat2(0.0f,0.25f));
	//ui_graphic_window_lb->queryInterface_IElement()->setSize(CFloat2(0.25f));
	//ui_graphic_window_lb->setColour(CFloatRGBA::sBlue);
	//auto ui_graphic_window_rb=ui_graphic_scene->createWindow("Test_RB");
	//ui_graphic_window_rb->queryInterface_IElement()->setPosition(CFloat2(0.25f,0.25f));
	//ui_graphic_window_rb->queryInterface_IElement()->setSize(CFloat2(0.25f));
	//ui_graphic_window_rb->setColour(CFloatRGBA::sWhite);
	struct SUIEvent
		:public NSUISystem::IEvent
		,public NSUISystem::IElement
	{
		enum EType
		{
			EType_MouseLeftButtonDown,
			EType_MouseRightButtonDown
		};
		const EType mType;
		CFloat2 mPosition;
		Int32 mOrder;
		SUIEvent(EType type)
			:mType(type)
			,mPosition(CFloat2(1000000.0f))
			,mOrder(0)
		{}
		virtual IElement * queryInterface_IElement() const override
		{
			return const_cast<SUIEvent*>(this);
		}
		virtual UInt32 getType() const override
		{
			return mType;
		}
		virtual const String & getName() const override
		{
			return CStringConverter::sBlank;
		}
		virtual Void setCoordParent(IElement * parent) override
		{

		}
		virtual IElement * getCoordParent() const override
		{
			return nullptr;
		}
		virtual Void setOrderParent(IElement * parent) override
		{

		}
		virtual IElement * getOrderParent() const override
		{
			return nullptr;
		}
		virtual Void setPosition(const CFloat2 & position) override
		{
			mPosition=position;
		}
		virtual const CFloat2 & getPosition() const override
		{
			return mPosition;
		}
		virtual const CFloat2 & getDerivedPosition() const override
		{
			return mPosition;
		}
		virtual Void setSize(const CFloat2 & size) override
		{
		}
		virtual const CFloat2 & getSize() const override
		{
			return CFloat2::sZero;
		}
		virtual const CFloat2 & getDerivedSize() const override
		{
			return CFloat2::sZero;
		}
		virtual Void setOrder(Int32 order) override
		{
			mOrder=order;
		}
		virtual Int32 getOrder()const
		{
			return mOrder;
		}
		virtual Int32 getDerivedOrder() const override
		{
			return mOrder;
		}
		virtual CFloat2 convertSize(const CFloat2 & size,ECoord fromCoord,ECoord toCoord) const override
		{
			return CFloat2::sZero;
		}
		virtual CFloat2 convertPosition(const CFloat2 & position,ECoord fromCoord,ECoord toCoord) const override
		{
			return CFloat2::sZero;
		}
		virtual Void setEnable(Bool enable) override
		{

		}
		virtual Bool getEnable() const override
		{
			return True;
		}
	};
	SUIEvent mouse_left_button_down_event(SUIEvent::EType_MouseLeftButtonDown);
	SUIEvent mouse_right_button_down_event(SUIEvent::EType_MouseRightButtonDown);
	struct SUIEventListener
		:public NSUISystem::IEventListener
	{
		const String mDescription;
		SUIEventListener(const String & description)
			:mDescription(description)
		{}
		virtual Void onEvent(NSUISystem::IEvent * e) override
		{
			std::cout<<"UI Event:Type="<<e->getType()<<";Description="<<mDescription<<std::endl;
		}
	};
	auto ui_event_scene=NSUISystem::getSystem()->createEventScene("Test");
	SUIEventListener ui_event_listener_lt("Test_LT");
	auto ui_event_window_lt=ui_event_scene->createWindow("Test_LT");
	ui_event_window_lt->queryInterface_IElement()->setPosition(CFloat2::sZero);
	ui_event_window_lt->queryInterface_IElement()->setSize(CFloat2(0.25f));
	ui_event_window_lt->registerListener(&ui_event_listener_lt,SUIEvent::EType_MouseLeftButtonDown);
	ui_event_window_lt->registerListener(&ui_event_listener_lt,SUIEvent::EType_MouseRightButtonDown);
	SUIEventListener ui_event_listener_rt("Test_RT");
	auto ui_event_window_rt=ui_event_scene->createWindow("Test_RT");
	ui_event_window_rt->queryInterface_IElement()->setPosition(CFloat2(0.25f,0.0f));
	ui_event_window_rt->queryInterface_IElement()->setSize(CFloat2(0.25f));
	ui_event_window_rt->registerListener(&ui_event_listener_rt,SUIEvent::EType_MouseLeftButtonDown);
	ui_event_window_rt->registerListener(&ui_event_listener_rt,SUIEvent::EType_MouseRightButtonDown);
	SUIEventListener ui_event_listener_lb("Test_LB");
	auto ui_event_window_lb=ui_event_scene->createWindow("Test_LB");
	ui_event_window_lb->queryInterface_IElement()->setPosition(CFloat2(0.0f,0.25f));
	ui_event_window_lb->queryInterface_IElement()->setSize(CFloat2(0.25f));
	ui_event_window_lb->registerListener(&ui_event_listener_lb,SUIEvent::EType_MouseLeftButtonDown);
	ui_event_window_lb->registerListener(&ui_event_listener_lb,SUIEvent::EType_MouseRightButtonDown);
	SUIEventListener ui_event_listener_rb("Test_RB");
	auto ui_event_window_rb=ui_event_scene->createWindow("Test_RB");
	ui_event_window_rb->queryInterface_IElement()->setPosition(CFloat2(0.25f,0.25f));
	ui_event_window_rb->queryInterface_IElement()->setSize(CFloat2(0.25f));
	ui_event_window_rb->registerListener(&ui_event_listener_rb,SUIEvent::EType_MouseLeftButtonDown);
	ui_event_window_rb->registerListener(&ui_event_listener_rb,SUIEvent::EType_MouseRightButtonDown);

	CTransform3DNode camera_node;
	camera_node.setPosition(CFloat3(0,1.0f,0));

	CTimer timer;
	auto yaw=0.0f;
	auto pitch=0.0f;
	auto mouse=NSInputSystem::getSystem()->getVirtualDeviceManager()->createMouse("Mouse",NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDevice(0));
	auto keyboard=NSInputSystem::getSystem()->getVirtualDeviceManager()->createKeyboard("Keyboard",NSInputSystem::getSystem()->getPhysicalDeviceManager()->getDevice(1));
	while(keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_ESCAPE)!=NSInputSystem::IEnum::EButtonState_Pressed)
	{
		for(UInt32 i=0;i<render_viewport->getQueryDatasCount();++i)
			std::cout<<"Last Viewport Query:"<<i<<":"<<render_viewport->getQueryDatas()[i]<<std::endl;
		query->setArea(CFloat2(-1.0f),CFloat2(-1.0f));
		CInt2 cursor_pos=window.getCursorPosition();
		auto delta_time=timer.getInMillisecond();
		NSInputSystem::getSystem()->update();
		String temp;
		temp.resize(256);
		sprintf_s(&temp[0],temp.size(),"%d,%d",mouse->getPosition().x,mouse->getPosition().y);
		std::cout<<"Mouse Position:"<<temp.c_str();

		temp.clear();
		temp.resize(256);
		sprintf_s(&temp[0],temp.size(),"Left:%s,Right:%s,Middle:%s"
			,mouse->getButtonState(NSInputSystem::IEnum::EMouseButtonType_Left)==NSInputSystem::IEnum::EButtonState_Pressed?"Pressed":"Released"
			,mouse->getButtonState(NSInputSystem::IEnum::EMouseButtonType_Right)==NSInputSystem::IEnum::EButtonState_Pressed?"Pressed":"Released"
			,mouse->getButtonState(NSInputSystem::IEnum::EMouseButtonType_Middle)==NSInputSystem::IEnum::EButtonState_Pressed?"Pressed":"Released"
			);
		std::cout<<" Button State:"<<temp.c_str();

		temp.clear();
		temp.resize(256);
		sprintf_s(&temp[0],temp.size(),"%d",mouse->getWheelPosition());
		std::cout<<" WheelPosition:"<<temp.c_str();
		std::cout<<std::endl;
		NSPhysicalSystem::getSystem()->update();
		physical_ray_query->execute();
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_W))
			camera_node.setPosition(camera_node.getPosition()+camera_node.getDirection()*static_cast<Float>(delta_time)*0.001f*10.0f);
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_S))
			camera_node.setPosition(camera_node.getPosition()-camera_node.getDirection()*static_cast<Float>(delta_time)*0.001f*10.0f);
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_A))
			camera_node.setPosition(camera_node.getPosition()-camera_node.getRight()*static_cast<Float>(delta_time)*0.001f*10.0f);
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_D))
			camera_node.setPosition(camera_node.getPosition()+camera_node.getRight()*static_cast<Float>(delta_time)*0.001f*10.0f);
		if(NSInputSystem::IEnum::EButtonState_Pressed==keyboard->getButtonState(NSInputSystem::IEnum::EKeyType_SPACE))
		{
			++current_window_size_index;
			current_window_size_index=current_window_size_index%(sizeof(window_size)/sizeof(UInt32));
			window.setSize(CUInt2(window_size[current_window_size_index],window_size[current_window_size_index]));
		}
		if(NSInputSystem::IEnum::EButtonState_Pressed==mouse->getButtonState(NSInputSystem::IEnum::EMouseButtonType_Left))
		{
			mouse_left_button_down_event.setPosition(cursor_pos/static_cast<Float>(window_size[current_window_size_index]));
			query->setArea(cursor_pos/static_cast<Float>(window_size[current_window_size_index]),cursor_pos/static_cast<Float>(window_size[current_window_size_index]));
		}
		else
		{
			mouse_left_button_down_event.setPosition(CFloat2(10000.0f));
		}
		if(NSInputSystem::IEnum::EButtonState_Pressed==mouse->getButtonState(NSInputSystem::IEnum::EMouseButtonType_Right))
		{
			pitch=std::max<Float>(pitch,-90.0f);
			pitch=std::min<Float>(pitch,90.0f);
			camera_node.setRotation(yaw,0,pitch);

			mouse_right_button_down_event.setPosition(cursor_pos/static_cast<Float>(window_size[current_window_size_index]));
		}
		else
		{
			mouse_right_button_down_event.setPosition(CFloat2(10000.0f));
		}
		render_camera->queryInterface_ISceneElement()->getTransformer()->setPosition(camera_node.getDerivedPosition());
		render_camera->queryInterface_ISceneElement()->getTransformer()->setOrientation(camera_node.getDerivedOrientation());
		NSRenderSystem::getSystem()->update();
		NSNetworkSystem::getSystem()->update();

		ui_event_scene->route(&mouse_left_button_down_event);
		ui_event_scene->route(&mouse_right_button_down_event);

		if(PeekMessage(&msg,static_cast<HWND>(window.getHandle()),0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	NSUISystem::getSystem()->shutdown();
	NSInputSystem::getSystem()->shutdown();
	NSPhysicalSystem::getSystem()->shutdown();
	NSRenderSystem::getSystem()->shutdown();
	NSNetworkSystem::getSystem()->shutdown();
	NSResourceSystem::getSystem()->shutdown();
	DEVILX_TRACK_SHUTDOWN;
    return 0;
}

