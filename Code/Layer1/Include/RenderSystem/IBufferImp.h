#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBufferImp
			:public IBuffer
			,public TBaseObject<IBufferImp>
			,public CMessageNotifier
			,public CDirtyFlagContainer
			,public CReferenceObject
		{
		public:
			enum EMessage
			{
				EMessage_BeginDirtyFlagAdd,
				EMessage_EndDirtyFlagAdd
			};
			enum EDirtyFlag
			{
				EDirtyFlag_Size,
				EDirtyFlag_Datas,
			};
			enum EType
			{
				EType_VertexBuffer,
				EType_IndexBuffer
			};
			struct SDirties
				:public CRangesI
			{
				using CRangesI::CRangesI;
				Void addDirty(UInt32 offset,UInt32 count)
				{
					addRange(CRangeI(offset,count+offset-1));
				}
			};
		protected:
			const String mName;
			const EType mType;
			ConstVoidPtr mDatas;
			UInt32 mSizeInBytes;
			IBufferImp::SDirties mDirties;
		public:
			IBufferImp(const String & name,EType type=EType_VertexBuffer);
			EType getType()const
			{
				return mType;
			}
			const ConstVoidPtr & getDatasRef()const
			{
				return mDatas;
			}
			const decltype(mDirties) & getDirties()const
			{
				return mDirties;
			}
			// Í¨¹ý IBuffer ¼Ì³Ð
			virtual const String & getName() const override;
			virtual Void setSize(UInt32 sizeInBytes) override;
			virtual UInt32 getSize() const override;
			virtual Void setDatas(ConstVoidPtr datas) override;
			virtual ConstVoidPtr getDatas() const override;
			virtual Void updateData(UInt32 offsetInBytes=0,UInt32 sizeInBytes=0) override;
		protected:
			~IBufferImp();
			virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagRemove(UInt32 flagIndex) override;
		};
	}
}