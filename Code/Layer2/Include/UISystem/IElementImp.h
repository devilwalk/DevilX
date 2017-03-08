#pragma once
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IElementImp
			:public IElement
			,public TBaseObject<IElementImp>
			,public CMessageNotifier
			,public TMessageReceiver<IElementImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginDerivedPositionChange,
				EMessage_EndDerivedPositionChange,
				EMessage_BeginDerivedSizeChange,
				EMessage_EndDerivedSizeChange,
				EMessage_BeginDerivedOrderChange,
				EMessage_EndDerivedOrderChange
			};
		protected:
			const String mName;
			CFloat2 mPosition;
			CFloat2 mDerivedPosition;
			CFloat2 mSize;
			CFloat2 mDerivedSize;
			Int32 mOrder;
			Int32 mDerivedOrder;
			IElementImp * mParent;
		public:
			IElementImp(const String & name);
			virtual ~IElementImp();
			// 通过 IElement 继承
			virtual const String & getName() const override;
			virtual Void setParent(IElement * parent) override;
			virtual IElement * getParent() const override;
			virtual Void setPosition(const CFloat2 & position) override;
			virtual const CFloat2 & getPosition() const override;
			virtual const CFloat2 & getDerivedPosition() const override;
			virtual Void setSize(const CFloat2 & size) override;
			virtual const CFloat2 & getSize() const override;
			virtual const CFloat2 & getDerivedSize() const override;
			virtual Void setOrder(Int32 order) override;
			virtual Int32 getOrder() const override;
			virtual Int32 getDerivedOrder() const override;
			virtual CFloat2 convertSize(const CFloat2 & relativeSize) const override;
			virtual CFloat2 convertPosition(const CFloat2 & relativePosition) const override;
		protected:
			Void _updateDerivedPosition();
			Void _updateDerivedSize();
			Void _updateDerivedOrder();

			// 通过 TMessageReceiver 继承
			virtual Void onMessage(IElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}