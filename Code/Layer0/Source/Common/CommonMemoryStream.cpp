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

Boolean NSDevilX::CMemoryStreamReader::move(Int32 offset)
{
	return setPosition(mPosition+offset);
}

Boolean NSDevilX::CMemoryStreamReader::process(UInt32 sizeInBytes,OUT VoidPtr dst)
{
	Boolean ret=CDataStreamReader::mStream->getSize()>=mPosition+sizeInBytes;
	if(ret)
	{
		memcpy(static_cast<CharPtr>(dst),&static_cast<CMemoryStream*>(mStream)->getData()[mPosition],sizeInBytes);
		move(static_cast<Int32>(sizeInBytes));
	}
	return ret;
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

Boolean NSDevilX::CMemoryStreamWriter::move(Int32 offset)
{
	return setPosition(mPosition+offset);
}

Boolean NSDevilX::CMemoryStreamWriter::process(ConstVoidPtr src,UInt32 sizeInBytes)
{
	if((mPosition+sizeInBytes)>mStream->getSize())
		static_cast<CMemoryStream*>(mStream)->getData().resize(mPosition+sizeInBytes);
	memcpy(&static_cast<CMemoryStream*>(mStream)->getData()[mPosition],src,sizeInBytes);
	move(static_cast<Int32>(sizeInBytes));
	return true;
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

CDataStreamReader * NSDevilX::CMemoryStream::createReader()
{
	return DEVILX_NEW CMemoryStreamReader(this);
}

Void NSDevilX::CMemoryStream::destroyReader(CDataStreamReader * reader)
{
	DEVILX_DELETE(static_cast<CMemoryStreamReader*>(reader));
}

CDataStreamWriter * NSDevilX::CMemoryStream::createWriter()
{
	return DEVILX_NEW CMemoryStreamWriter(this);
}

Void NSDevilX::CMemoryStream::destroyWrite(CDataStreamWriter * writer)
{
	DEVILX_DELETE(static_cast<CMemoryStreamWriter*>(writer));
}

UInt32 NSDevilX::CMemoryStream::getSize() const
{
	return static_cast<UInt32>(mData.size());
}
