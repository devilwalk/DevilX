#pragma once
#include "Common.h"
#include "Include.h"
#include "GLES3/gl32.h"
#include "EGL/egl.h"
#define DEVILX_RENDERSYSTEM_GLES3_ST 0
#define DEVILX_RENDERSYSTEM_GLES3_MT 1
#define DEVILX_RENDERSYSTEM_GLES3_MODE DEVILX_RENDERSYSTEM_GLES3_ST
#include "GLES3BaseObject.h"
#include "GLES3ClearViewportProgram.h"
#include "GLES3Enum.h"
#include "GLES3Utility.h"
#include "GLES3Camera.h"
#include "GLES3ConstantBuffer.h"
#include "GLES3ConstantBufferContainer.h"
#include "GLES3ConstantBufferDescription.h"
#include "GLES3ConstantBufferDescriptionManager.h"
#include "GLES3DepthStencil.h"
#include "GLES3EntityImp.h"
#include "GLES3EntityMaterial.h"
#include "GLES3EntityPass.h"
#include "GLES3EntityTechnique.h"
#include "GLES3ForwardPixelShaderGenerator.h"
#include "GLES3ForwardVertexShaderGenerator.h"
#include "GLES3Geometry.h"
#include "GLES3IndexBufferImp.h"
#include "GLES3Light.h"
#include "GLES3OverlayManager.h"
#include "GLES3OverlayMaterial.h"
#include "GLES3OverlayMaterialManager.h"
#include "GLES3OverlayRenderable.h"
#include "GLES3Pass.h"
#include "GLES3Program.h"
#include "GLES3RenderOperation.h"
#include "GLES3RenderTarget.h"
#include "GLES3RenderTargetImp.h"
#include "GLES3RenderTask.h"
#include "GLES3Resource.h"
#include "GLES3SamplerObject.h"
#include "GLES3Scene.h"
#include "GLES3ShaderManager.h"
#include "GLES3SubEntityImp.h"
#include "GLES3SystemImp.h"
#include "GLES3Texture.h"
#include "GLES3TransformerImp.h"
#include "GLES3VertexBufferImp.h"
#include "GLES3Viewport.h"
#include "GLES3ViewportImp.h"
#include "GLES3WindowImp.h"