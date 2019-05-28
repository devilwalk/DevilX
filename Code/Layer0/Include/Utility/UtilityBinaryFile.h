#pragma once
#include "UtilitySTL.h"
#include "UtilityDataStream.h"
namespace NSDevilX
{
	class CBinaryFileChunk
		:public TBaseObject<CBinaryFileChunk>
	{
	public:
		struct SChunkBase
		{
			friend class CBinaryFileChunk;
		public:
			virtual Void writeTo(VoidPtr & dst,Bool movePointer=True)const;
			virtual Void writeTo(CDataStreamWriter * writer,Bool movePointer=True)const;
			virtual Boolean readFrom(VoidPtr & src,Bool movePointer=True);
			virtual Boolean readFrom(CDataStreamReader * reader,Bool movePointer=True);
		protected:
			virtual ConstVoidPtr _getWritePointer()const=0;
			virtual UInt32 _getWriteSize()const=0;
			virtual VoidPtr _getReadPointer()=0;
			virtual UInt32 _getReadSize()const=0;
		};
		struct STagChunk
			:public SChunkBase
			,public TBaseObject<STagChunk>
		{
		protected:
			std::array<Char,8> mValue;
		public:
			STagChunk();
			STagChunk(const String & tag);
			Boolean operator==(const STagChunk & chunk)const;
		protected:
			virtual ConstVoidPtr _getWritePointer()const override;
			virtual UInt32 _getWriteSize()const override;
			virtual VoidPtr _getReadPointer()override;
			virtual UInt32 _getReadSize()const override;
		};
		struct SSizeChunk
			:public TBaseObject<SSizeChunk>
			,public SChunkBase
		{
		protected:
			UInt32 & mSizeInBytesRef;
		public:
			static UInt32 getSize()
			{
				return sizeof(UInt32);
			}
			SSizeChunk(UInt32 & sizeInBytesRef);
			UInt32 getValue()const
			{
				return mSizeInBytesRef;
			}
		protected:
			virtual ConstVoidPtr _getWritePointer()const override;
			virtual UInt32 _getWriteSize()const override;
			virtual VoidPtr _getReadPointer()override;
			virtual UInt32 _getReadSize()const override;
		};
		struct SDataChunk
			:public SChunkBase
			,public TBaseObject<SDataChunk>
		{
		protected:
			SSizeChunk * mSizeChunk;
			DevilXTVector(Byte) mData;
		public:
			SDataChunk();
			SDataChunk(ConstVoidPtr data,UInt32 sizeInBytes);
			~SDataChunk();
			ConstBytePtr getData()const
			{
				if(getSizeInBytes())
					return &mData[SSizeChunk::getSize()];
				else
					return nullptr;
			}
			UInt32 getSizeInBytes()const
			{
				return mSizeChunk?mSizeChunk->getValue():0;
			}
			virtual Boolean readFrom(VoidPtr & src,Bool movePointer=True) override;
			virtual Boolean readFrom(CDataStreamReader * reader,Bool movePointer=True) override;
		protected:
			virtual ConstVoidPtr _getWritePointer()const override;
			virtual UInt32 _getWriteSize()const override;
			virtual VoidPtr _getReadPointer()override;
			virtual UInt32 _getReadSize()const override;
		};
		struct SStringChunk
			:public SDataChunk
		{
		public:
			SStringChunk();
			SStringChunk(const String & value);
			String getValue()const;
		};
		static const STagChunk msBegin;
		static const STagChunk msEnd;
	protected:
		SStringChunk mName;
		SDataChunk mData;
	public:
		CBinaryFileChunk();
		CBinaryFileChunk(const String & name,ConstVoidPtr data,UInt32 sizeInBytes);
		~CBinaryFileChunk();
		String getName()const
		{
			return mName.getValue();
		}
		ConstBytePtr getData()const
		{
			return mData.getData();
		}
		String getDataInString()const
		{
			return static_cast<const SStringChunk*>(&mData)->getValue();
		}
		UInt32 getSizeInBytes()const
		{
			return mData.getSizeInBytes();
		}
		Void writeTo(VoidPtr & dst,Bool movePointer=True)const;
		Void writeTo(CDataStreamWriter * writer);
		Boolean readFrom(VoidPtr & src,Bool movePointer=True);
		Boolean readFrom(CDataStreamReader * reader,Bool movePointer=True);
	};
	class CBinaryFile
		:public TBaseObject<CBinaryFile>
	{
	public:
		typedef DevilXTVector(CBinaryFileChunk*) Chunks;
	protected:
		Chunks mChunks;
	public:
		CBinaryFile();
		Boolean addChunk(const String & name,ConstVoidPtr data,UInt32 sizeInBytes);
		const CBinaryFileChunk * getChunk(const String & name)const;
		const CBinaryFileChunk * getChunk(SizeT index)const
		{
			return mChunks[index];
		}
		UInt32 getChunkCount()const
		{
			return static_cast<UInt32>(mChunks.size());
		}
		Void writeTo(CDataStream * dataStream);
		Boolean readFrom(CDataStream * dataStream);
	};
}