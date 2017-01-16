#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CSystemImp;
			class CViewport;
			class CLight;
			class CRenderTask
			{
			protected:
				CViewport * const mViewport;
				TVector<CRenderTask*> mTasks;
			public:
				CRenderTask(CViewport * viewport);
				virtual ~CRenderTask();
				CViewport * getViewport()const
				{
					return mViewport;
				}
				Void prepare(){}
				virtual Void process();
				Void clearState(){}
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
						virtual Void process() override;
					};
				protected:
					CLight * mLight;
				public:
					CLightTask(CLight * light,CViewport * viewport);
					~CLightTask();
					Void setLight(CLight * light)
					{
						mLight=light;
					}
					virtual Void process() override;
				};
			protected:
				TVector<CLightTask*> mLightTaskPool;
			public:
				CRenderSceneForwardTask(CViewport * viewport);
				~CRenderSceneForwardTask();
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
				virtual Void process() override;
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
				virtual Void process() override;
			};
		}
	}
}