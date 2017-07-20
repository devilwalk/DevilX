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
			struct SDirties
				:public CRangesI
			{
				using CRangesI::CRangesI;
				Void addDirty(UInt32 offset=0,UInt32 count=0)
				{
					addRange(CRangeI(offset,count+offset-1));
				}
			};
		protected:
			UInt32 mCount;
			const UInt32 * mIndices;
			SDirties mIndicesDirties;
		public:
			IIndexBufferImp();
			const SDirties & getIndicesDirties()const
			{
				return mIndicesDirties;
			}
			const UInt32 * const & getIndicesRef()const
			{
				return mIndices;
			}
			// Inherited via IIndexBuffer
			virtual Void setCount(UInt32 count) override;
			virtual UInt32 getCount() const override;
			virtual Void setIndices(const UInt32 * indices,UInt32 count=0) override;
			virtual Void updateIndices(UInt32 offset=0,UInt32 count=0) override;
			virtual const UInt32 * getIndices() const override;
		protected:
			~IIndexBufferImp();
			virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagRemove(UInt32 flagIndex) override;
		};
	}
}