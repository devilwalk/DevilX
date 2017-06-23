#pragma once
#include "GLES3ShaderManager.h"
#include "GLES3ConstantBufferDescriptionManager.h"
#include "GLES3ConstantBufferContainer.h"
#include "GLES3DepthStencil.h"
#include "GLES3RenderTargetImp.h"
#include "GLES3WindowImp.h"
#include "GLES3Scene.h"
#include "GLES3VertexBufferImp.h"
#include "GLES3IndexBufferImp.h"
#include "GLES3Texture.h"
#include "GLES3TransformerImp.h"
#include "GLES3ClearViewportProgram.h"
#include "GLES3OverlayMaterialManager.h"
#include "GLES3SamplerObject.h"
#include "GLESSL3_2DefnitionShaderCodeFunction.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CSystemImp
				:public TBaseObject<CSystemImp>
				,public TSingleton<CSystemImp>
				,public CConstantBufferContainer
				,public TMessageReceiver<IResourceManagerImp>
				,public TMessageReceiver<ISystemImp>
				,public CMessageNotifier
			{
			public:
				enum EMessage
				{
					EMessage_BeginFrame,
					EMessage_EndFrame
				};
			protected:
				CThreadPool * mRenderTaskThreadPool;
				EGLDisplay mDisplay;
				EGLContext mContext;
				CShaderManager * mShaderManager;
				NSGLESSL3_2::CDefinitionShader * mDefinitionShader;
				CConstantBufferDescriptionManager * mConstantBufferDescriptionManager;
				CClearViewportProgram * mClearViewportProgram;
				COverlayMaterialManager * mOverlayMaterialManager;
				TResourcePtrVector<CDepthStencil> mDepthStencils;
				TResourcePtrVector<CSamplerObject> mSamplerObjects;
				TResourcePtrMap<IWindowImp*const,CWindowImp> mWindows;
				TResourcePtrMap<ISceneImp*const,CScene> mScenes;
				TResourcePtrMap<IVertexBufferImp*const,CVertexBufferImp> mVertexBuffers;
				TResourcePtrMap<IIndexBufferImp*const,CIndexBufferImp> mIndexBuffers;
				TResourcePtrMap<IGeometryImp*const,CGeometry> mGeometrys;
				TResourcePtrMap<ITexture2DImp*const,CTexture2D> mTexture2Ds;
				TResourcePtrMap<ITransformerImp*const,CTransformerImp> mTransformers;
				TResourcePtrMap<ConstVoidPtr,Void> mInstanceByInternals;
			public:
				CSystemImp();
				~CSystemImp();
				decltype(mRenderTaskThreadPool) getRenderTaskThreadPool()const
				{
					return mRenderTaskThreadPool;
				}
				decltype(mContext) getContext()const
				{
					return mContext;
				}
				CShaderManager * getShaderManager()const
				{
					return mShaderManager;
				}
				decltype(mDefinitionShader) getDefinitionShader()const
				{
					return mDefinitionShader;
				}
				CConstantBufferDescriptionManager * getConstantBufferDescriptionManager()const
				{
					return mConstantBufferDescriptionManager;
				}
				CDepthStencil * getFreeDepthStencil();
				CSamplerObject * getDefaultSamplerObject()const;
				CSamplerObject * getSamplerObject(const SSamplerDescription & desc);
				CProgram * getClearViewportProgram()const
				{
					return mClearViewportProgram->getProgram();
				}
				COverlayMaterialManager * getOverlayMaterialManager()const
				{
					return mOverlayMaterialManager;
				}
				CWindowImp * getWindow(IWindowImp * interfaceImp)const
				{
					return mWindows.get(interfaceImp);
				}
				CScene * getScene(ISceneImp * interfaceImp)const
				{
					return mScenes.get(interfaceImp);
				}
				CVertexBufferImp * getVertexBuffer(IVertexBufferImp * interfaceImp)const
				{
					return mVertexBuffers.get(interfaceImp);
				}
				CIndexBufferImp * getIndexBuffer(IIndexBufferImp * interfaceImp)const
				{
					return mIndexBuffers.get(interfaceImp);
				}
				CGeometry * getGeometry(IGeometryImp * interfaceImp)const
				{
					return mGeometrys.get(interfaceImp);
				}
				CTexture * getTexture(ITextureImp * tex)const
				{
					switch(tex->getType())
					{
					case IEnum::ETextureType_2D:
						return mTexture2Ds.get(static_cast<ITexture2DImp*>(tex));
					case IEnum::ETextureType_Cube:
						break;
					}
					return nullptr;
				}
				CTransformerImp * createTransformer(ITransformerImp * interfaceImp);
				CTransformerImp * getTransformer(ITransformerImp * interfaceImp)const
				{
					return mTransformers.get(interfaceImp);
				}
				Void destroyTransformer(ITransformerImp * interfaceImp)
				{
					mTransformers.destroy(interfaceImp);
				}
				VoidPtr getInstanceByInternal(ConstVoidPtr interfaceImp)const
				{
					return mInstanceByInternals.get(interfaceImp);
				}
				Boolean hasInstanceByInternal(ConstVoidPtr interfaceImp)const
				{
					return mInstanceByInternals.has(interfaceImp);
				}
				Void addInstanceByInternal(ConstVoidPtr interfaceImp,VoidPtr instance)
				{
					mInstanceByInternals.add(interfaceImp,instance);
				}
				Void removeInstanceByInternal(ConstVoidPtr interfaceImp)
				{
					mInstanceByInternals.erase(interfaceImp);
				}
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IResourceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}