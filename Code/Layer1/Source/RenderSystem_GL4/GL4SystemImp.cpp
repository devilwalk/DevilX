#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;
ISystem * NSDevilX::NSRenderSystem::getSystem()
{
	if(!CSystemImp::getSingletonPtr())
		DEVILX_NEW CSystemImp;
	return ISystemImp::getSingletonPtr();
}

NSDevilX::NSRenderSystem::NSGL4::CSystemImp::CSystemImp()
	:CConstantBufferContainer("cbSystem")
	,mRenderTaskThreadPool(nullptr)
	,mContext(nullptr)
	,mShaderManager(nullptr)
	,mDefinitionShader(nullptr)
	,mConstantBufferDescriptionManager(nullptr)
	,mClearViewportProgram(nullptr)
	,mOverlayMaterialManager(nullptr)
{
	DEVILX_NEW ISystemImp();
	mRenderTaskThreadPool=DEVILX_NEW CThreadPool(4);
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	WNDCLASSEX wnd_class;
	wnd_class.cbClsExtra=0;
	wnd_class.cbSize=sizeof(WNDCLASSEX);
	wnd_class.cbWndExtra=0;
	wnd_class.hbrBackground=reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wnd_class.hCursor=LoadCursor(GetModuleHandle(nullptr),IDC_ARROW);
	wnd_class.hIcon=nullptr;
	wnd_class.hIconSm=nullptr;
	wnd_class.hInstance=GetModuleHandle(nullptr);
	wnd_class.lpfnWndProc=DefWindowProc;
	wnd_class.lpszClassName=_T("Temp");
	wnd_class.lpszMenuName=nullptr;
	wnd_class.style=CS_HREDRAW|CS_VREDRAW;
	RegisterClassEx(&wnd_class);
	auto wnd=CreateWindowEx(0,wnd_class.lpszClassName,_T("Temp"),WS_POPUP,0,0,1,1,nullptr,nullptr,wnd_class.hInstance,nullptr);
	ShowWindow(wnd,SW_NORMAL);
	UpdateWindow(wnd);
	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	auto dc=GetDC(wnd);
	auto fmt=ChoosePixelFormat(dc,&pfd);
	SetPixelFormat(dc,fmt,&pfd);
	auto context=wglCreateContext(dc);
	wglMakeCurrent(dc,context);
	glewInit();
	wglMakeCurrent(nullptr,nullptr);
	wglDeleteContext(context);
	const Int32 attrib_list[]=
	{
		WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
		WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,32,
		WGL_DEPTH_BITS_ARB,24,
		WGL_STENCIL_BITS_ARB,8,
		0,        //End
	};
	Int32 pixel_format=0;
	UInt32 num_formats=0;
	wglChoosePixelFormatARB(dc,attrib_list,nullptr,1,&pixel_format,&num_formats);
	SetPixelFormat(dc,pixel_format,&PIXELFORMATDESCRIPTOR());
	Int32 attrs[]=
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB,4,
		WGL_CONTEXT_MINOR_VERSION_ARB,5,
		WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifdef DEVILX_DEBUG
		WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
		0
	};
	mContext=wglCreateContextAttribsARB(dc,nullptr,attrs);
	wglMakeCurrent(dc,getContext());
	ReleaseDC(wnd,dc);
	DestroyWindow(wnd);
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
#ifdef DEVILX_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	CUtility::checkGLError();
	glDebugMessageCallback([](GLenum source,GLenum type,GLuint id,GLenum serverity,GLsizei length,const GLchar *message,const GLvoid *userParam)
	{
		OutputDebugStringA(message);
		OutputDebugStringA("\r\n");
	},nullptr);
	CUtility::checkGLError();
#endif
	mShaderManager=DEVILX_NEW CShaderManager;
	mDefinitionShader=DEVILX_NEW NSGLSL4_5::CDefinitionShader;
	mConstantBufferDescriptionManager=DEVILX_NEW CConstantBufferDescriptionManager;
	mOverlayMaterialManager=DEVILX_NEW COverlayMaterialManager();
	mClearViewportProgram=DEVILX_NEW CClearViewportProgram;
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_EndWindowCreate);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_BeginWindowDestroy);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_EndSceneCreate);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_BeginSceneDestroy);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Update);
	ISystemImp::getSingleton().addListener(static_cast<TMessageReceiver<ISystemImp>*>(this),ISystemImp::EMessage_Destruction);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_EndGeometryCreate);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_BeginGeometryDestroy);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_EndTextureCreate);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_BeginTextureDestroy);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_VertexBufferCreate);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_VertexBufferDestroy);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_IndexBufferCreate);
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->addListener(static_cast<TMessageReceiver<IResourceManagerImp>*>(this),IResourceManagerImp::EMessage_IndexBufferDestroy);
}

NSDevilX::NSRenderSystem::NSGL4::CSystemImp::~CSystemImp()
{
	DEVILX_DELETE(mRenderTaskThreadPool);
	DEVILX_DELETE(mClearViewportProgram);
	DEVILX_DELETE(mOverlayMaterialManager);
	DEVILX_DELETE(mConstantBufferDescriptionManager);
	DEVILX_DELETE(mDefinitionShader);
	DEVILX_DELETE(mShaderManager);
	wglMakeCurrent(nullptr,nullptr);
	wglDeleteContext(getContext());
}

CDepthStencil * NSDevilX::NSRenderSystem::NSGL4::CSystemImp::getFreeDepthStencil()
{
	CDepthStencil * ret=nullptr;
	for(auto ds:mDepthStencils)
	{
		if(!ds->getLocked())
		{
			ret=ds;
			break;
		}
	}
	if(!ret)
	{
		ret=DEVILX_NEW CDepthStencil();
		mDepthStencils.push_back(ret);
	}
	return ret;
}

CTransformerImp * NSDevilX::NSRenderSystem::NSGL4::CSystemImp::createTransformer(ITransformerImp * interfaceImp)
{
	if(getTransformer(interfaceImp))
		return nullptr;
	auto ret=DEVILX_NEW CTransformerImp(interfaceImp);
	mTransformers[interfaceImp]=ret;
	return ret;
}

Void NSDevilX::NSRenderSystem::NSGL4::CSystemImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case ISystemImp::EMessage_Update:
		notify(EMessage_BeginFrame);
		needUpdate();
		for(auto const & window_pair:mWindows)
		{
			auto window=window_pair.second;
			window->prepare();
		}
		for(auto const & window_pair:mWindows)
		{
			auto window=window_pair.second;
			window->render();
		}
		notify(EMessage_EndFrame);
		break;
	case ISystemImp::EMessage_EndWindowCreate:
	{
		CWindowImp * window=DEVILX_NEW CWindowImp(static_cast<IWindowImp*>(data));
		mWindows[static_cast<IWindowImp*>(data)]=window;
	}
	break;
	case ISystemImp::EMessage_BeginWindowDestroy:
	{
		mWindows.destroy(static_cast<IWindowImp*>(data));
	}
	break;
	case ISystemImp::EMessage_EndSceneCreate:
	{
		auto * scene=DEVILX_NEW CScene(static_cast<ISceneImp*>(data));
		mScenes[static_cast<ISceneImp*>(data)]=scene;
	}
	break;
	case ISystemImp::EMessage_BeginSceneDestroy:
	{
		mScenes.destroy(static_cast<ISceneImp*>(data));
	}
	break;
	case ISystemImp::EMessage_Destruction:
		DEVILX_DELETE(this);
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CSystemImp::onMessage(IResourceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case IResourceManagerImp::EMessage_EndGeometryCreate:
		mGeometrys[static_cast<IGeometryImp*>(data)]=DEVILX_NEW CGeometry(static_cast<IGeometryImp*>(data));
		break;
	case IResourceManagerImp::EMessage_BeginGeometryDestroy:
		mGeometrys.destroy(static_cast<IGeometryImp*>(data));
		break;
	case IResourceManagerImp::EMessage_EndTextureCreate:
		switch(static_cast<ITextureImp*>(data)->getType())
		{
		case IEnum::ETextureType_2D:
			mTexture2Ds[static_cast<ITexture2DImp*>(static_cast<ITextureImp*>(data))]=DEVILX_NEW CTexture2D(static_cast<ITexture2DImp*>(static_cast<ITextureImp*>(data)));
			break;
		case IEnum::ETextureType_Cube:
			break;
		}
		break;
	case IResourceManagerImp::EMessage_BeginTextureDestroy:
		switch(static_cast<ITextureImp*>(data)->getType())
		{
		case IEnum::ETextureType_2D:
			mTexture2Ds.destroy(static_cast<ITexture2DImp*>(static_cast<ITextureImp*>(data)));
			break;
		case IEnum::ETextureType_Cube:
			break;
		}
		break;
	case IResourceManagerImp::EMessage_VertexBufferCreate:
		mVertexBuffers[static_cast<IVertexBufferImp*>(data)]=DEVILX_NEW CVertexBufferImp(static_cast<IVertexBufferImp*>(data));
		break;
	case IResourceManagerImp::EMessage_VertexBufferDestroy:
		mVertexBuffers.destroy(static_cast<IVertexBufferImp*>(data));
		break;
	case IResourceManagerImp::EMessage_IndexBufferCreate:
		mIndexBuffers[static_cast<IIndexBufferImp*>(data)]=DEVILX_NEW CIndexBufferImp(static_cast<IIndexBufferImp*>(data));
		break;
	case IResourceManagerImp::EMessage_IndexBufferDestroy:
		mIndexBuffers.destroy(static_cast<IIndexBufferImp*>(data));
		break;
	}
}
Void NSDevilX::NSRenderSystem::NSGL4::CSystemImp::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gFrameTimeInSeconds").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=ISystemImp::getSingleton().getFrameTimeInSecond();
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseFrameTimeInSeconds").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f/ISystemImp::getSingleton().getFrameTimeInSecond();
}