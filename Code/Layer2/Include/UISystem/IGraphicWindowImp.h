#pragma once
#include "IElementImp.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IGraphicSceneImp;
		class IGraphicWindowImp
			:public IGraphicWindow
			,public TBaseObject<IGraphicWindowImp>
			,public TMessageReceiver<IElementImp>
		{
		protected:
			IGraphicSceneImp * const mScene;
			IElementImp * mElement;
			NSRenderSystem::IOverlayElement * mRenderOverlayElement;
			CSInt2 mPixelStart,mPixelEnd;
		public:
			IGraphicWindowImp(const String & name,IGraphicSceneImp * scene);
			~IGraphicWindowImp();
			// 通过 IImageWindow 继承
			virtual IElement * queryInterface_IElement() const override;
			virtual Void setTexture(NSRenderSystem::ITexture * texture,const CSInt2 & pixelStart,const CSInt2 & pixelEnd) override;
			virtual NSRenderSystem::ITexture * getTexture() const override;
			virtual const CSInt2 & getPixelStart() const override;
			virtual const CSInt2 & getPixelEnd() const override;
			virtual Void setColour(const CColour & colour) override;
			virtual const CColour & getColour() const override;

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(IElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}