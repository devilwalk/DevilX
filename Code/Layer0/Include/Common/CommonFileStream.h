#pragma once
#include "CommonDataStream.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CFileStream;
	class CFileStreamReader
		:public CDataStreamReader
		,public TBaseObject<CFileStreamReader>
	{
	protected:
		std::ifstream mStream;
	public:
		CFileStreamReader(CFileStream * stream);
		~CFileStreamReader();

		// Inherited via CDataStreamReader
		virtual Boolean setPosition(UInt32 position) override;
		virtual Boolean move(Int32 offset) override;
		virtual Boolean process(UInt32 sizeInBytes,OUT VoidPtr dst) override;
	};
	class CFileStreamWriter
		:public CDataStreamWriter
		,public TBaseObject<CFileStreamWriter>
	{
	protected:
		std::ofstream mStream;
	public:
		CFileStreamWriter(CFileStream * stream);
		~CFileStreamWriter();

		// Inherited via CDataStreamWriter
		virtual Boolean setPosition(UInt32 position) override;
		virtual Boolean move(Int32 offset) override;
		virtual Boolean process(ConstVoidPtr src,UInt32 sizeInBytes) override;
	};
	class CFileStream
		:public CDataStream
		,public TBaseObject<CFileStream>
	{
	protected:
		const String mFullName;
		UInt32 mSizeInBytes;
	public:
		CFileStream(const String & fullName);
		~CFileStream();
		const String & getFullName()const
		{
			return mFullName;
		}

		// Inherited via CDataStream
		virtual UInt32 getSize() const override;
		virtual CDataStreamReader * createReader() const override;
		virtual Void destroyReader(CDataStreamReader * reader) const override;
		virtual CDataStreamWriter * createWriter() const override;
		virtual Void destroyWrite(CDataStreamWriter * writer) const override;
	};
}