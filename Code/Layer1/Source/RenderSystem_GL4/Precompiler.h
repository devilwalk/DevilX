#pragma once
#include "Common.h"
#include "Include.h"
#include "GL/glew.h"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
	#include "GL/wglew.h"
	#include "GL/wglext.h"
#elif DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_X
	#include "GL/glxew.h";
	#include "GL/glxext.h";
#endif
#define DEVILX_RENDERSYSTEM_GL4_ST 0
#define DEVILX_RENDERSYSTEM_GL4_MT 1
#define DEVILX_RENDERSYSTEM_GL4_MODE DEVILX_RENDERSYSTEM_GL4_ST
#include "GL4BaseObject.h"
#include "GL4Enum.h"
#include "GL4Utility.h"
#include "GL4Camera.h"
#include "GL4ConstantBuffer.h"
#include "GL4ConstantBufferContainer.h"
#include "GL4ConstantBufferDescription.h"
#include "GL4ConstantBufferDescriptionManager.h"
#include "GL4DepthStencil.h"
#include "GL4ForwardPixelShaderGenerator.h"
#include "GL4ForwardVertexShaderGenerator.h"
#include "GL4Geometry.h"
#include "GL4IndexBufferImp.h"
#include "GL4Light.h"
#include "GL4Material.h"
#include "GL4Pass.h"
#include "GL4Program.h"
#include "GL4Renderable.h"
#include "GL4RenderableObject.h"
#include "GL4RenderOperation.h"
#include "GL4RenderTarget.h"
#include "GL4RenderTargetImp.h"
#include "GL4RenderTask.h"
#include "GL4Scene.h"
#include "GL4ShaderManager.h"
#include "GL4SystemImp.h"
#include "GL4Technique.h"
#include "GL4Texture.h"
#include "GL4TransformerImp.h"
#include "GL4VertexBuffer.h"
#include "GL4VertexBufferImp.h"
#include "GL4Viewport.h"
#include "GL4ViewportImp.h"
#include "GLSL4_5DefnitionShaderCodeFunction.h"