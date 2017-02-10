#pragma once
#include "IElementImp.h"
#include "RenderRectangle.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IGraphicWindowImp
			:public IGraphicWindow
			,public TBaseObject<IGraphicWindowImp>
			,public TMessageReceiver<IElementImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginImageChange,
				EMessage_EndImageChange,
				EMessage_BeginColourChange,
				EMessage_EndColourChange
			};
		protected:
			IElementImp * mElement;
			const CImage * mImage;
			CFloat2 mUVStart;
			CFloat2 mUVEnd;
			CColour mColour;
			CRenderRectangle * mRenderRectangle;
		public:
			IGraphicWindowImp(const String & name);
			~IGraphicWindowImp();

			// ͨ�� IImageWindow �̳�
			virtual IElement * queryInterface_IElement() const override;
			virtual Void setImage(const CImage * img,DirectX::FXMVECTOR pixelStartVec,DirectX::FXMVECTOR pixelEndVec) override;
			virtual Void setColour(const CColour & colour) override;
			virtual const CColour & getColour() const override;

			// ͨ�� TMessageReceiver �̳�
			virtual Void onMessage(IElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		protected:
			Void _updateRenderRectangle();
		};
	}
}