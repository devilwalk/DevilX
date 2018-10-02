#pragma once
#include "RenderTask.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CViewport;
		class CRenderTaskMT
			:public CRenderTask
		{
		protected:
			UInt32 mThreadSyncGroupID;
		public:
			CRenderTaskMT();
			virtual ~CRenderTaskMT();
			Void submit();
			virtual Void process() override;
		protected:
			virtual Boolean _needSubmit()const;
		};
		class CClearTask
			:public CRenderTaskMT
		{
		protected:
			CRenderTarget * mRenderTarget;
			CDepthStencil * mDepthStencil;
		public:
			CClearTask();
			~CClearTask();
			Void setRenderTarget(CRenderTarget * renderTarget)
			{
				mRenderTarget=renderTarget;
			}
			Void setDepthStencil(CDepthStencil * depthStencil)
			{
				mDepthStencil=depthStencil;
			}
		protected:
			virtual Void _prepare() override;
		};
		class CRenderSceneTask
			:public CRenderTaskMT
		{
		protected:
			CViewport * mViewport;
			UInt8 mRenderQueueIDStart;
			UInt8 mRenderQueueIDEnd;
		public:
			CRenderSceneTask();
			~CRenderSceneTask();
			Void setViewport(CViewport * viewport)
			{
				mViewport=viewport;
			}
		protected:
			virtual Void _prepare() override;
		};
	}
}