#pragma once
#include "CommonType.h"
#include "CommonSTL.h"
#include "CommonDataStream.h"
namespace NSDevilX
{
	class CBinaryFileChunk
		:public TBaseObject<CBinaryFileChunk>
	{
	public:
		struct SChunkBase
		{
		public:
			Void writeTo(VoidPtr & dst,Bool movePointer=True)const;
			Void writeTo(CDataStreamWriter * writer)const;
			Boolean readFrom(VoidPtr & src,Bool movePointer=True);
			Boolean readFrom(CDataStreamReader * reader,Bool movePointer=True);
		protected:
			virtual Void _preWriteTo(VoidPtr & dst,Bool movePointer=True)const;
			virtual Void _preWriteTo(CDataStreamWriter * writer)const;
			virtual Boolean _preReadFrom(VoidPtr & src,Bool movePointer=True);
			virtual Boolean _preReadFrom(CDataStreamReader * reader,Bool movePointer=True);
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
			UInt32 mSizeInBytes;
		public:
			SSizeChunk();
			SSizeChunk(UInt32 sizeInBytes);
			UInt32 getValue()const
			{
				return mSizeInBytes;
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
			TVector<Byte> mData;
		public:
			SDataChunk();
			SDataChunk(ConstBytePtr data,UInt32 sizeInBytes);
			ConstBytePtr getData()const
			{
				if(getSizeInBytes())
					return &mData[0];
				else
					return nullptr;
			}
			UInt32 getSizeInBytes()const
			{
				return static_cast<UInt32>(mData.size());
			}
		protected:
			virtual Void _preWriteTo(VoidPtr & dst,Bool movePointer=True)const override;
			virtual Void _preWriteTo(CDataStreamWriter * writer)const override;
			virtual Boolean _preReadFrom(VoidPtr & src,Bool movePointer=True)override;
			virtual Boolean _preReadFrom(CDataStreamReader * reader,Bool movePointer=True)override;
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
			const String getValue()const;
		};
		static const STagChunk msBegin;
		static const STagChunk msEnd;
	protected:
		SStringChunk mName;
		SDataChunk mData;
	public:
		CBinaryFileChunk();
		CBinaryFileChunk(const String & name,ConstBytePtr data,UInt32 sizeInBytes);
		~CBinaryFileChunk();
		String getName()const
		{
			return mName.getValue();
		}
		ConstBytePtr getData()const
		{
			return mData.getData();;
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
		typedef TVector<CBinaryFileChunk*> Chunks;
	protected:
		Chunks mChunks;
	public:
		CBinaryFile();
		Boolean addChunk(const String & name,ConstBytePtr data,UInt32 sizeInBytes);
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