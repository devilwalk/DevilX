#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSystemImp;
			class CViewport;
			class CLight;
			class CRenderTask
			{
			protected:
				CViewport * const mViewport;
				ID3D11DeviceContext1 * mContext;
				ID3D11CommandList * mCommandList;
				UInt32 mThreadSyncGroupID;
				TVector<CRenderTask*> mTasks;
			public:
				CRenderTask(CViewport * viewport);
				virtual ~CRenderTask();
				CViewport * getViewport()const
				{
					return mViewport;
				}
				ID3D11CommandList * getCommandList()const
				{
					return mCommandList;
				}
				Void submit();
				virtual Void prepare();
				virtual Void process();
				Void clearState();
			};
			class CClearViewportTask
				:public CRenderTask
				,public TBaseObject<CClearViewportTask>
				,public CConstantBufferContainer
			{
			protected:
				CColour mClearColour[8];
				Float mClearDepth;
				Int32 mClearStencil;
			public:
				CClearViewportTask(CViewport * viewport);
				~CClearViewportTask();
				Void setClearColour(UInt32 renderTargetIndex,const CColour & colour)
				{
					if(colour!=mClearColour[renderTargetIndex])
					{
						mClearColour[renderTargetIndex]=colour;
						needUpdate();
					}
				}
				Void setClearDepth(Float depth)
				{
					if(depth!=mClearDepth)
					{
						mClearDepth=depth;
						needUpdate();
					}
				}
				Void setClearStencil(Int32 stencil)
				{
					if(stencil!=mClearStencil)
					{
						mClearStencil=stencil;
						needUpdate();
					}
				}
				virtual Void process() override;

				// Inherited via CConstantBufferContainer
				virtual Void _updateConstantBuffer(Byte * buffer) override;
			};
			class CRenderSceneForwardTask
				:public CRenderTask
				,public TBaseObject<CRenderSceneForwardTask>
			{
			public:
				class CAmbientTask
					:public CRenderTask
					,public TBaseObject<CAmbientTask>
				{
				public:
					CAmbientTask(CViewport * viewport);
					~CAmbientTask();
					virtual Void process() override;
				};
				class CLightTask
					:public CRenderTask
					,public TBaseObject<CLightTask>
				{
				public:
					class CShadowMapTask
						:public CRenderTask
						,public TBaseObject<CShadowMapTask>
					{
					public:
						CShadowMapTask(CViewport * viewport);
						~CShadowMapTask();
					protected:
						virtual Void prepare() override;
					};
				protected:
					CLight * mLight;
					TVector<CConstantBuffer*> mSubmitConstantBuffers;
				public:
					CLightTask(CLight * light,CViewport * viewport);
					~CLightTask();
					Void setLight(CLight * light)
					{
						mLight=light;
					}
					virtual Void prepare() override;
					virtual Void process() override;
				};
			protected:
				TVector<CLightTask*> mLightTaskPool;
			public:
				CRenderSceneForwardTask(CViewport * viewport);
				~CRenderSceneForwardTask();
				virtual Void prepare() override;
				virtual Void process() override;
			};
			class CForwardRenderTask
				:public CRenderTask
				,public TBaseObject<CForwardRenderTask>
			{
			public:
				CForwardRenderTask(CViewport * viewport);
				~CForwardRenderTask();
				Void setClearColour(const CColour & colour);
				Void setClearDepth(Float depth);
				Void setClearStencil(Int32 stencil);
				virtual Void prepare() override;
			};
			class CRenderSceneGBufferTask
				:public CRenderTask
				,public TBaseObject<CRenderSceneGBufferTask>
			{
			protected:
			public:
				CRenderSceneGBufferTask(CViewport * viewport);
				~CRenderSceneGBufferTask();
			protected:
				virtual Void prepare() override;
			};
		}
	}
}