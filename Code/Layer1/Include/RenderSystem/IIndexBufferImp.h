#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometryImp;
		class IIndexBufferImp
			:public IIndexBuffer
			,public TBaseObject<IIndexBufferImp>
			,public CDirtyFlagContainer
			,public CReferenceObject
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginDirtyFlagAdd,
				EMessage_EndDirtyFlagAdd
			};
			enum EDirtyFlag
			{
				EDirtyFlag_Count,
				EDirtyFlag_Index
			};
		protected:
			UInt32 mCount;
			const UInt32 * mIndices;
		public:
			IIndexBufferImp();

			// Inherited via IIndexBuffer
			virtual Void setCount(UInt32 count) override;
			virtual UInt32 getCount() const override;
			virtual Void setIndices(const UInt32 * indices) override;
			virtual Void updateIndices() override;
			virtual const UInt32 * getIndices() const override;
		protected:
			~IIndexBufferImp();
			virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex) override;
		};
	}
}