#pragma once
#include "IOverlayElementImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderTargetImp;
		class IViewportImp
			:public IViewport
			,public IOverlay
			,public TBaseObject<IViewportImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginCameraChange,
				EMessage_EndCameraChange,
				EMessage_BeginLeftChange,
				EMessage_EndLeftChange,
				EMessage_BeginTopChange,
				EMessage_EndTopChange,
				EMessage_BeginWidthChange,
				EMessage_EndWidthChange,
				EMessage_BeginHeightChange,
				EMessage_EndHeightChange,
				EMessage_BeginOrderChange,
				EMessage_EndOrderChange,
				EMessage_BeginTechniqueChange,
				EMessage_EndTechniqueChange,
				EMessage_BeginClearColourChange,
				EMessage_EndClearColourChange,
				EMessage_BeginOverlayElementCreate,
				EMessage_EndOverlayElementCreate,
				EMessage_BeginOverlayElementDestroy,
				EMessage_EndOverlayElementDestroy
			};
		protected:
			const String mName;
			IRenderTargetImp * const mRenderTarget;
			ICameraImp * mCamera;
			float mLeft,mTop,mWidth,mHeight;
			UInt32 mOrder;
			Int32 mTechnique;
			CFloatRGBA mClearColour;
			TNamedResourcePtrMap<IOverlayElementImp> mOverlayElements;
		public:
			IViewportImp(const String & name,IRenderTargetImp * rt);
			~IViewportImp();
			IRenderTargetImp * getRenderTarget()const
			{
				return mRenderTarget;
			}
			Boolean isFullViewport()const;
			// Inherited via IViewport
			virtual IOverlay * queryInterface_IOverlay() const override;
			virtual const String & getName() const override;
			virtual Void setCamera(ICamera * camera) override;
			virtual ICamera * getCamera() const override;
			virtual Void setLeft(Float left) override;
			virtual Float getLeft() const override;
			virtual Void setTop(Float top) override;
			virtual Float getTop() const override;
			virtual Void setWidth(Float width) override;
			virtual Float getWidth() const override;
			virtual Void setHeight(Float height) override;
			virtual Float getHeight() const override;
			virtual Void setOrder(UInt32 order) override;
			virtual UInt32 getOrder() const override;
			virtual Void setTechnique(IEnum::ERenderTechnique technique) override;
			virtual IEnum::ERenderTechnique getTechnique() const override;
			virtual Void setClearColour(const CColour & colour) override;
			virtual const CColour & getClearColour() const override;

			// ͨ�� IOverlay �̳�
			virtual IOverlayElement * createElement(const String & name) override;
			virtual IOverlayElement * getElement(const String & name) const override;
			virtual Void destroyElement(IOverlayElement * element) override;
		};
	}
}