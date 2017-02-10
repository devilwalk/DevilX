#pragma once
#include "D3D11Shader.h"
#include "D3D11WindowImp.h"
#include "D3D11RenderableSurfaceImp.h"
#include "D3D11Geometry.h"
#include "D3D11ClearViewportShader.h"
#include "D3D11Scene.h"
#include "D3D11ShaderCodeManager.h"
#include "D3D11ConstantBufferDescriptionManager.h"
#include "D3D11ConstantBufferContainer.h"
#include "D3D11Enum.h"
#include "D3D11DepthStencil.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
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
				struct SInputLayout
					:public TBaseObject<SInputLayout>
				{
					TVector<D3D11_INPUT_ELEMENT_DESC> mDescs;
					ID3D11InputLayout * mInternal;
					~SInputLayout()
					{
						mInternal->Release();
					}
				};
				enum EMessage
				{
					EMessage_BeginFrame,
					EMessage_EndFrame
				};
			protected:
				CEnum::EShaderModelType mShaderModelType;
				IDXGIFactory1 * mFactory;
				ID3D11Device1 * mDevice;
				ID3D11DeviceContext1 * mImmediateContext;
				ID3D11Debug * mDebug;
				CThreadPool * mRenderTaskThreadPool;
				CShaderCodeManager * mShaderCodeManager;
				CConstantBufferDescriptionManager * mConstantBufferDescriptionManager;
				union
				{
					NSHLSL5::CDefinitionShader * mDefinitionShader5;
					NSHLSL4_1::CDefinitionShader * mDefinitionShader4_1;
				};
				D3D_FEATURE_LEVEL mSupport;
				CClearViewportShader * mClearViewportShader;
				TVector<SInputLayout*> mInputLayouts;
				TVector<CDepthStencil*> mDepthStencils;
				TResourcePtrContainer<ID3DBlob*,CVertexShader> mVertexShaders;
				TResourcePtrContainer<ID3DBlob*,CPixelShader> mPixelShaders;
				TVector<ID3D11RasterizerState1*> mRasterizerStates;
				TVector<ID3D11BlendState1*> mBlendStates;
				TVector<ID3D11DepthStencilState*> mDepthStencilStates;
				TVector<ID3D11SamplerState*> mSamplerStates;
				TResourcePtrContainer<IWindowImp*const,CWindowImp> mWindows;
				TResourcePtrContainer<IRenderableSurfaceImp*const,CRenderableSurfaceImp> mRenderableSurfaces;
				TResourcePtrContainer<ISceneImp*const,CScene> mScenes;
				TResourcePtrContainer<IGeometryImp*const,CGeometry> mGeometrys;
				TResourcePtrContainer<ITexture2DImp*const,CTexture2D> mTexture2Ds;
				TResourcePtrContainer<IVertexBufferImp*const,CVertexBufferImp> mVertexBuffers;
				TResourcePtrContainer<IIndexBufferImp*const,CIndexBufferImp> mIndexBuffers;
				TResourcePtrContainer<ITransformerImp*,CTransformer> mTransformers;
				D3D11_RASTERIZER_DESC1 mDefaultRasterizerStateDesc;
				D3D11_BLEND_DESC1 mDefaultBlendStateDesc;
				D3D11_DEPTH_STENCIL_DESC mDefaultDepthStencilDesc;
				D3D11_SAMPLER_DESC mDefaultSamplerDesc;
				TResourcePtrContainer<ConstVoidPtr,Void> mInstanceByInternals;
				TResourcePtrContainer<const IUnknown*,Void> mInstanceByCOMInternals;
			public:
				CSystemImp();
				~CSystemImp();
				CEnum::EShaderModelType getShaderModelType()const
				{
					return mShaderModelType;
				}
				IDXGIFactory1 * getDXGIFactory()const
				{
					return mFactory;
				}
				ID3D11Device1 * getDevice()const
				{
					return mDevice;
				}
				ID3D11DeviceContext1 * getImmediateContext()const
				{
					return mImmediateContext;
				}
				ID3D11Debug * getDebug()const
				{
					return mDebug;
				}
				CClearViewportShader * getClearViewportShader()const
				{
					return mClearViewportShader;
				}
				CThreadPool * getRenderTaskThreadPool()const
				{
					return mRenderTaskThreadPool;
				}
				CShaderCodeManager * getShaderCodeManager()const
				{
					return mShaderCodeManager;
				}
				CConstantBufferDescriptionManager * getConstantBufferDescriptionManager()const
				{
					return mConstantBufferDescriptionManager;
				}
				NSHLSL5::CDefinitionShader * getDefinitionShader5()const
				{
					return mDefinitionShader5;
				}
				NSHLSL4_1::CDefinitionShader * getDefinitionShader4_1()const
				{
					return mDefinitionShader4_1;
				}
				CDepthStencil * getFreeDepthStencil();
				ID3D11InputLayout * getInputLayout(const D3D11_INPUT_ELEMENT_DESC * descs,UINT numElements);
				ID3D11RasterizerState1 * getRasterizerState(const D3D11_RASTERIZER_DESC1 & desc);
				ID3D11BlendState1 * getBlendState(const D3D11_BLEND_DESC1 & desc);
				ID3D11DepthStencilState * getDepthStencilState(const D3D11_DEPTH_STENCIL_DESC & desc);
				ID3D11SamplerState * getSamplerState(const D3D11_SAMPLER_DESC & desc);
				CVertexShader * getVertexShader(ID3DBlob * code);
				CPixelShader * getPixelShader(ID3DBlob * code);
				CScene * getScene(ISceneImp * interfaceImp)const
				{
					return mScenes.get(interfaceImp);
				}
				CWindowImp * getWindow(IWindowImp * interfaceImp)const
				{
					return mWindows.get(interfaceImp);
				}
				CRenderableSurfaceImp * getRenderableSurface(IRenderableSurfaceImp * interfaceImp)const
				{
					return mRenderableSurfaces.get(interfaceImp);
				}
				CRenderTargetImp * getRenderTarget(IRenderTargetImp * interfaceImp)const
				{
					if(dynamic_cast<IRenderableSurfaceImp*>(interfaceImp))
						return getRenderableSurface(static_cast<IRenderableSurfaceImp*>(interfaceImp));
					else
						return getWindow(static_cast<IWindowImp*>(interfaceImp));
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
				CVertexBufferImp * getVertexBuffer(IVertexBufferImp * interfaceImp)const
				{
					return mVertexBuffers.get(interfaceImp);
				}
				CIndexBufferImp * getIndexBuffer(IIndexBufferImp * interfaceImp)const
				{
					return mIndexBuffers.get(interfaceImp);
				}
				CTransformer * createTransformer(ITransformerImp * interfaceImp);
				CTransformer * getTransformer(ITransformerImp * interfaceImp)const
				{
					return mTransformers.get(interfaceImp);
				}
				Void destroyTransformer(ITransformerImp * interfaceImp)
				{
					mTransformers.destroy(interfaceImp);
				}
				const D3D11_RASTERIZER_DESC1 & getDefaultRasterizerStateDescription()const
				{
					return mDefaultRasterizerStateDesc;
				}
				const D3D11_BLEND_DESC1 & getDefaultBlendStateDescription()const
				{
					return mDefaultBlendStateDesc;
				}
				const D3D11_DEPTH_STENCIL_DESC & getDefaultDepthStencilDescription()const
				{
					return mDefaultDepthStencilDesc;
				}
				const D3D11_SAMPLER_DESC & getDefaultSamplerStateDescription()const
				{
					return mDefaultSamplerDesc;
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
				VoidPtr getInstanceByCOMInternal(const IUnknown * interfaceImp)const
				{
					return mInstanceByCOMInternals.get(interfaceImp);
				}
				Boolean hasInstanceByCOMInternal(const IUnknown * interfaceImp)const
				{
					return mInstanceByCOMInternals.has(interfaceImp);
				}
				Void addInstanceByCOMInternal(const IUnknown * interfaceImp,VoidPtr instance)
				{
					mInstanceByCOMInternals.add(interfaceImp,instance);
				}
				Void removeInstanceByCOMInternal(const IUnknown * interfaceImp)
				{
					mInstanceByCOMInternals.erase(interfaceImp);
				}
				// Inherited via TMessageReceiver
				virtual Void onMessage(ISystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(IResourceManagerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
		}
	}
}