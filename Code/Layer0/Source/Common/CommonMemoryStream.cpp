#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CMemoryStreamReader::CMemoryStreamReader(CMemoryStream * stream)
	:CDataStreamReader(stream)
	,mPosition(0)
{}

NSDevilX::CMemoryStreamReader::~CMemoryStreamReader()
{}

Boolean NSDevilX::CMemoryStreamReader::setPosition(UInt32 position)
{
	Boolean ret=mStream->getSize()>position;
	if(ret)
		mPosition=position;
	return ret;
}

UInt32 NSDevilX::CMemoryStreamReader::getPosition() const
{
	return mPosition;
}

Boolean NSDevilX::CMemoryStreamReader::move(Int32 offset)
{
	return setPosition(mPosition+offset);
}

UInt32 NSDevilX::CMemoryStreamReader::process(UInt32 sizeInBytes,OUT VoidPtr dst)
{
	sizeInBytes=std::min<>(sizeInBytes,CDataStreamReader::mStream->getSize()-mPosition);
	if(sizeInBytes)
	{
		memcpy(static_cast<CharPtr>(dst),&static_cast<CMemoryStream*>(mStream)->getData()[mPosition],sizeInBytes);
		move(static_cast<Int32>(sizeInBytes));
	}
	return sizeInBytes;
}

NSDevilX::CMemoryStreamWriter::CMemoryStreamWriter(CMemoryStream * stream)
	:CDataStreamWriter(stream)
	,mPosition(0)
{}

NSDevilX::CMemoryStreamWriter::~CMemoryStreamWriter()
{}

Boolean NSDevilX::CMemoryStreamWriter::setPosition(UInt32 position)
{
	mPosition=position;
	return true;
}

UInt32 NSDevilX::CMemoryStreamWriter::getPosition() const
{
	return mPosition;
}

Boolean NSDevilX::CMemoryStreamWriter::move(Int32 offset)
{
	return setPosition(mPosition+offset);
}

UInt32 NSDevilX::CMemoryStreamWriter::process(ConstVoidPtr src,UInt32 sizeInBytes)
{
	if((mPosition+sizeInBytes)>mStream->getSize())
		static_cast<CMemoryStream*>(mStream)->getData().resize(mPosition+sizeInBytes);
	memcpy(&static_cast<CMemoryStream*>(mStream)->getData()[mPosition],src,sizeInBytes);
	move(static_cast<Int32>(sizeInBytes));
	return sizeInBytes;
}

NSDevilX::CMemoryStream::CMemoryStream()
{}

NSDevilX::CMemoryStream::CMemoryStream(CFileStream * stream)
{
	mData.resize(stream->getSize());
	CDataStreamReader * reader=stream->createReader();
	reader->process(stream->getSize(),&mData[0]);
	stream->destroyReader(reader);
}

NSDevilX::CMemoryStream::~CMemoryStream()
{}

CDataStreamReader * NSDevilX::CMemoryStream::createReader() const
{
	return DEVILX_NEW CMemoryStreamReader(const_cast<CMemoryStream*>(this));
}

Void NSDevilX::CMemoryStream::destroyReader(CDataStreamReader * reader) const
{
	DEVILX_DELETE(static_cast<CMemoryStreamReader*>(reader));
}

CDataStreamWriter * NSDevilX::CMemoryStream::createWriter() const
{
	return DEVILX_NEW CMemoryStreamWriter(const_cast<CMemoryStream*>(this));
}

Void NSDevilX::CMemoryStream::destroyWrite(CDataStreamWriter * writer) const
{
	DEVILX_DELETE(static_cast<CMemoryStreamWriter*>(writer));
}

UInt32 NSDevilX::CMemoryStream::getSize() const
{
	return static_cast<UInt32>(mData.size());
}
