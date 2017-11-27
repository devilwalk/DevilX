#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;
ISystem * NSDevilX::NSRenderSystem::getSystem()
{
	if(!CSystemImp::getSingletonPtr())
		DEVILX_NEW CSystemImp;
	return ISystemImp::getSingletonPtr();
}

NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::CSystemImp()
	:CConstantBufferContainer("cbSystem")
	,mRenderTaskThreadPool(nullptr)
	,mContext(EGL_NO_CONTEXT)
	,mDisplay(EGL_NO_DISPLAY)
	,mShaderManager(nullptr)
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
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
	mDisplay=eglGetDisplay(EGL_DEFAULT_DISPLAY);
	CUtility::checkEGLError();
	eglInitialize(getDisplay(),nullptr,nullptr);
	CUtility::checkEGLError();
	eglBindAPI(EGL_OPENGL_ES_API);
	CUtility::checkEGLError();
	const EGLint config_attr[]=
	{
		EGL_RED_SIZE,8,
		EGL_GREEN_SIZE,8,
		EGL_BLUE_SIZE,8,
		EGL_ALPHA_SIZE,8,
		EGL_COLOR_BUFFER_TYPE,EGL_RGB_BUFFER,
		EGL_DEPTH_SIZE,24,
		EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
		EGL_STENCIL_SIZE,8,
		EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
		EGL_NONE
	};
	EGLConfig config=0;
	EGLint num_config=0;
	eglChooseConfig(getDisplay(),config_attr,&config,1,&num_config);
	CUtility::checkEGLError();
	const EGLint context_attr[]={
		EGL_CONTEXT_MAJOR_VERSION,3,
		EGL_CONTEXT_MINOR_VERSION,2,
		EGL_NONE
	};
	mContext=eglCreateContext(getDisplay(),config,EGL_NO_CONTEXT,context_attr);
	CUtility::checkEGLError();
	auto surface=eglCreateWindowSurface(getDisplay(),config,wnd,nullptr);
	CUtility::checkEGLError();
	eglMakeCurrent(getDisplay(),surface,surface,getContext());
	CUtility::checkEGLError();
	eglDestroySurface(getDisplay(),surface);
	CUtility::checkEGLError();
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	DestroyWindow(wnd);
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
#endif
#if DEVILX_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	CUtility::checkGLError();
#endif
	mSamplerObjects.push_back(DEVILX_NEW CSamplerObject(SSamplerDescription()));
	mShaderManager=DEVILX_NEW CShaderManager;
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

NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::~CSystemImp()
{
	DEVILX_DELETE(mRenderTaskThreadPool);
	DEVILX_DELETE(mClearViewportProgram);
	DEVILX_DELETE(mOverlayMaterialManager);
	DEVILX_DELETE(mConstantBufferDescriptionManager);
	DEVILX_DELETE(mShaderManager);
	mSamplerObjects.destroyAll();
	mDepthStencils.destroyAll();
	mVertexBuffers.destroyAll();
	mIndexBuffers.destroyAll();
	mTexture2Ds.destroyAll();
	mWindows.destroyAll();
	mScenes.destroyAll();
	mTransformers.destroyAll();
	DEVILX_DELETE(mConstantBuffer);
	mConstantBuffer=nullptr;
	eglMakeCurrent(getDisplay(),EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
	CUtility::checkEGLError();
	eglDestroyContext(getDisplay(),getContext());
	CUtility::checkEGLError();
	eglTerminate(getDisplay());
	CUtility::checkEGLError();
	mInstanceByInternals.clear();
}

CDepthStencil * NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::getFreeDepthStencil()
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

CSamplerObject * NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::getDefaultSamplerObject() const
{
	return mSamplerObjects[0];
}

CSamplerObject * NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::getSamplerObject(const SSamplerDescription & desc)
{
	CSamplerObject * ret=nullptr;
	for(auto obj:mSamplerObjects)
	{
		if(obj->getDesc()==desc)
		{
			ret=obj;
			break;
		}
	}
	if(!ret)
	{
		ret=DEVILX_NEW CSamplerObject(desc);
		mSamplerObjects.push_back(ret);
	}
	return ret;
}

CTransformerImp * NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::createTransformer(ITransformerImp * interfaceImp)
{
	if(getTransformer(interfaceImp))
		return nullptr;
	auto ret=DEVILX_NEW CTransformerImp(interfaceImp);
	mTransformers[interfaceImp]=ret;
	return ret;
}

Void NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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

Void NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::onMessage(IResourceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
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
Void NSDevilX::NSRenderSystem::NSGLES3::CSystemImp::_updateConstantBuffer(Byte * buffer)
{
	auto offset=mConstantBuffer->getDescription()->getConstantDesc("gFrameTimeInSeconds").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=ISystemImp::getSingleton().getFrameTimeInSecond();
	offset=mConstantBuffer->getDescription()->getConstantDesc("gInverseFrameTimeInSeconds").mOffsetInBytes;
	*reinterpret_cast<Float*>(&buffer[offset])=1.0f/ISystemImp::getSingleton().getFrameTimeInSecond();
}