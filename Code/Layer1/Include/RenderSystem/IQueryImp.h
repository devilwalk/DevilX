#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IViewportImp;
		class IQueryImp
			:public IQuery
			,public TBaseObject<IQueryImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginAreaChange,
				EMessage_EndAreaChange
			};
		protected:
			const String mName;
			IViewportImp * const mViewport;
			CFloat2 mStartPosition;
			CFloat2 mEndPosition;
		public:
			IQueryImp(const String & name,IViewportImp * vp);
			~IQueryImp();

			// ͨ�� IQuery �̳�
			virtual const String & getName() const override;
			virtual IViewport * getViewport() const override;
			virtual Void setArea(const CFloat2 & startPosition,const CFloat2 & endPosition) override;
			virtual const CFloat2 & getStartPosition() const override;
			virtual const CFloat2 & getEndPosition() const override;
		};
	}
}