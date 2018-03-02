#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CFileStreamReader::CFileStreamReader(CFileStream * stream)
	:CDataStreamReader(stream)
	,mStream(stream->getFullName().c_str(),std::ios::binary|std::ios::in)
{}

NSDevilX::CFileStreamReader::~CFileStreamReader()
{}

Boolean NSDevilX::CFileStreamReader::setPosition(UInt32 position)
{
	Boolean ret=CDataStreamReader::mStream->getSize()>position;
	if(ret)
		mStream.seekg(position);
	return ret;
}

UInt32 NSDevilX::CFileStreamReader::getPosition() const
{
	return static_cast<UInt32>(const_cast<CFileStreamReader*>(this)->mStream.tellg());
}

Boolean NSDevilX::CFileStreamReader::move(Int32 offset)
{
	return setPosition(static_cast<Int32>(mStream.tellg())+offset);
}

UInt32 NSDevilX::CFileStreamReader::process(UInt32 sizeInBytes,OUT VoidPtr dst)
{
	mStream.read(reinterpret_cast<Char*>(dst),sizeInBytes);
	return static_cast<UInt32>(mStream.gcount());
}

NSDevilX::CFileStreamWriter::CFileStreamWriter(CFileStream * stream)
	:CDataStreamWriter(stream)
	,mStream(stream->getFullName().c_str(),std::ios::binary|std::ios::out)
{}

NSDevilX::CFileStreamWriter::~CFileStreamWriter()
{}

Boolean NSDevilX::CFileStreamWriter::setPosition(UInt32 position)
{
	mStream.seekp(position);
	return true;
}

UInt32 NSDevilX::CFileStreamWriter::getPosition() const
{
	return static_cast<UInt32>(const_cast<CFileStreamWriter*>(this)->mStream.tellp());
}

Boolean NSDevilX::CFileStreamWriter::move(Int32 offset)
{
	return setPosition(static_cast<Int32>(mStream.tellp())+offset);
}

UInt32 NSDevilX::CFileStreamWriter::process(ConstVoidPtr src,UInt32 sizeInBytes)
{
	mStream.write(reinterpret_cast<ConstCharPtr>(src),sizeInBytes);
	return sizeInBytes;
}

NSDevilX::CFileStream::CFileStream(const String & fullName)
	:mFullName(fullName)
	,mSizeInBytes(0)
{
	std::ifstream stream(getFullName().c_str(),std::ios::binary|std::ios::in);
	stream.seekg(0,stream.end);
	mSizeInBytes=static_cast<UInt32>(stream.tellg());
}

NSDevilX::CFileStream::~CFileStream()
{}

UInt32 NSDevilX::CFileStream::getSize() const
{
	return mSizeInBytes;
}

CDataStreamReader * NSDevilX::CFileStream::createReader() const
{
	return DEVILX_NEW CFileStreamReader(const_cast<CFileStream*>(this));
}

Void NSDevilX::CFileStream::destroyReader(CDataStreamReader * reader) const
{
	DEVILX_DELETE(static_cast<CFileStreamReader*>(reader));
}

CDataStreamWriter * NSDevilX::CFileStream::createWriter() const
{
	return DEVILX_NEW CFileStreamWriter(const_cast<CFileStream*>(this));
}

Void NSDevilX::CFileStream::destroyWrite(CDataStreamWriter * writer) const
{
	DEVILX_DELETE(static_cast<CFileStreamWriter*>(writer));
}
