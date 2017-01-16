#pragma once
#include "CommonFileStream.h"
namespace NSDevilX
{
	class CMemoryStream;
	class CMemoryStreamReader
		:public CDataStreamReader
		,public TBaseObject<CMemoryStreamReader>
	{
	protected:
		UInt32 mPosition;
	public:
		CMemoryStreamReader(CMemoryStream * stream);
		~CMemoryStreamReader();

		// Inherited via CDataStreamReader
		virtual Boolean setPosition(UInt32 position) override;
		virtual Boolean move(Int32 offset) override;
		virtual Boolean process(UInt32 sizeInBytes,OUT VoidPtr dst) override;
	};
	class CMemoryStreamWriter
		:public CDataStreamWriter
		,public TBaseObject<CMemoryStreamWriter>
	{
	protected:
		UInt32 mPosition;
	public:
		CMemoryStreamWriter(CMemoryStream * stream);
		~CMemoryStreamWriter();

		// Inherited via CDataStreamWriter
		virtual Boolean setPosition(UInt32 position) override;
		virtual Boolean move(Int32 offset) override;
		virtual Boolean process(ConstVoidPtr src,UInt32 sizeInBytes) override;
	};
	class CMemoryStream
		:public CDataStream
		,public TBaseObject<CMemoryStream>
	{
	public:
		typedef TVector<Byte> Data;
	protected:
		Data mData;
	public:
		CMemoryStream();
		CMemoryStream(CFileStream * stream);
		~CMemoryStream();
		Data & getData()
		{
			return mData;
		}
		const Data & getData()const
		{
			return mData;
		}

		// Inherited via CDataStream
		virtual CDataStreamReader * createReader() override;
		virtual Void destroyReader(CDataStreamReader * reader) override;
		virtual CDataStreamWriter * createWriter() override;
		virtual Void destroyWrite(CDataStreamWriter * writer) override;
		virtual UInt32 getSize() const override;
	};
}