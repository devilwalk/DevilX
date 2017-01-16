#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableImp;
		class IGeometryUsageImp
			:public IGeometryUsage
			,public TBaseObject<IGeometryUsageImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginVertexBufferOffsetChange,
				EMessage_EndVertexBufferOffsetChange,
				EMessage_BeginIndexBufferOffsetChange,
				EMessage_EndIndexBufferOffsetChange,
				EMessage_BeginVertexCountChange,
				EMessage_EndVertexCountChange,
				EMessage_BeginIndexCountChange,
				EMessage_EndIndexCountChange,
				EMessage_BeginOperationTypeChange,
				EMessage_EndOperationTypeChange
			};
		protected:
			IRenderableImp * const mRenderable;
			UInt32 mVertexBufferOffset,mIndexBufferOffset,mVertexCount,mIndexCount;
			IEnum::EOperationType mOperationType;
		public:
			IGeometryUsageImp(IRenderableImp * renderable);
			virtual ~IGeometryUsageImp();

			// Í¨¹ý ISubMesh ¼Ì³Ð
			virtual Void setVertexBufferOffset(UInt32 offset) override;
			virtual UInt32 getVertexBufferOffset() const override;
			virtual Void setIndexBufferOffset(UInt32 offset) override;
			virtual UInt32 getIndexBufferOffset() const override;
			virtual Void setVertexCount(UInt32 count) override;
			virtual UInt32 getVertexCount() const override;
			virtual Void setIndexCount(UInt32 count) override;
			virtual UInt32 getIndexCount() const override;
			virtual Void setOperationType(IEnum::EOperationType type) override;
			virtual IEnum::EOperationType getOperationType() const override;
		};
	}
}