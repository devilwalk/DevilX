#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBufferUsageImp
			:public IBufferUsage
			,public TBaseObject<IBufferUsageImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginOffsetChange,
				EMessage_EndOffsetChange,
				EMessage_BeginSizeChange,
				EMessage_EndSizeChange
			};
		protected:
			UInt32 mOffsetInBytes,mSizeInBytes;
		public:
			IBufferUsageImp();
			~IBufferUsageImp();

			// Í¨¹ý IBufferUsage ¼Ì³Ð
			virtual Void setOffset(UInt32 offsetInBytes) override;
			virtual UInt32 getOffset() const override;
			virtual Void setSize(UInt32 sizeInBytes) override;
			virtual UInt32 getSize() const override;
		};
	}
}