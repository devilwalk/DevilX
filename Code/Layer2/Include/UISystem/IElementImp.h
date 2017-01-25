#pragma once
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IElementImp
			:public IElement
			,public TBaseObject<IElementImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginPositionChange,
				EMessage_EndPositionChange,
				EMessage_BeginSizeChange,
				EMessage_EndSizeChange
			};
		protected:
			const String mName;
			CFloat3 mPosition;
			CFloat2 mSize;
		public:
			IElementImp(const String & name);
			virtual ~IElementImp();
			// Í¨¹ý IElement ¼Ì³Ð
			virtual const String & getName() const override;
			virtual Void setPosition(DirectX::FXMVECTOR positionVec) override;
			virtual const CFloat3 & getPosition() const override;
			virtual Void setSize(DirectX::FXMVECTOR sizeVec) override;
			virtual const CFloat2 & getSize() const override;
		};
	}
}