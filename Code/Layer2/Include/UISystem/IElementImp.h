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
				EMessage_EndSizeChange,
				EMessage_BeginOrderChange,
				EMessage_EndOrderChange
			};
		protected:
			const String mName;
			CFloat2 mPosition;
			CFloat2 mSize;
			Int32 mOrder;
		public:
			IElementImp(const String & name);
			virtual ~IElementImp();
			// Í¨¹ý IElement ¼Ì³Ð
			virtual const String & getName() const override;
			virtual Void setPosition(const CFloat2 & position) override;
			virtual const CFloat2 & getPosition() const override;
			virtual Void setSize(const CFloat2 & size) override;
			virtual const CFloat2 & getSize() const override;
			virtual Void setOrder(Int32 order) override;
			virtual Int32 getOrder() const override;
			virtual CFloat2 convertSize(const CFloat2 & relativeSize) const override;
			virtual CFloat2 convertPosition(const CFloat2 & relativePosition) const override;
		};
	}
}