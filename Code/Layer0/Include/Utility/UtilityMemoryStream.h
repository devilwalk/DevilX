#pragma once
#include "UtilityFileStream.h"
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
		virtual UInt32 getPosition() const override;
		virtual Boolean move(Int32 offset) override;
		virtual UInt32 process(UInt32 sizeInBytes,OUT VoidPtr dst) override;
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
		virtual UInt32 getPosition() const override;
		virtual Boolean move(Int32 offset) override;
		virtual UInt32 process(ConstVoidPtr src,UInt32 sizeInBytes) override;
	};
	class CMemoryStream
		:public CDataStream
		,public TBaseObject<CMemoryStream>
	{
	public:
		typedef TVector(Byte) Data;
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
		Void load(CFileStream * stream);
		// Inherited via CDataStream
		virtual CDataStreamReader * createReader() const override;
		virtual Void destroyReader(CDataStreamReader * reader) const override;
		virtual CDataStreamWriter * createWriter() const override;
		virtual Void destroyWrite(CDataStreamWriter * writer) const override;
		virtual UInt32 getSize() const override;
	};
}