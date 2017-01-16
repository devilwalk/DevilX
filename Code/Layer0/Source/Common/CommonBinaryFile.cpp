#include "Precompiler.h"
using namespace NSDevilX;

Void NSDevilX::CBinaryFileChunk::SChunkBase::writeTo(VoidPtr & dst,Bool movePointer) const
{
	if(!_getWriteSize())
		return;
	_preWriteTo(dst,movePointer);
	memcpy(dst,_getWritePointer(),_getWriteSize());
	if(movePointer)
	{
		dst=static_cast<BytePtr>(dst)+_getWriteSize();
	}
}

Void NSDevilX::CBinaryFileChunk::SChunkBase::writeTo(CDataStreamWriter * writer) const
{
	if(!_getWriteSize())
		return;
	_preWriteTo(writer);
	writer->process(_getWritePointer(),_getWriteSize());
}

Boolean NSDevilX::CBinaryFileChunk::SChunkBase::readFrom(VoidPtr & src,Bool movePointer)
{
	if(_preReadFrom(src,movePointer))
	{
		memcpy(_getReadPointer(),src,_getReadSize());
		if(movePointer)
		{
			src=static_cast<BytePtr>(src)+_getReadSize();
		}
		return true;
	}
	else
	{
		return false;
	}
}

Boolean NSDevilX::CBinaryFileChunk::SChunkBase::readFrom(CDataStreamReader * reader,Bool movePointer)
{
	Boolean ret=_preReadFrom(reader,movePointer);
	if(ret)
	{
		ret&=reader->process(_getReadSize(),_getReadPointer());
		if(!movePointer)
			reader->move(-static_cast<Int32>(_getReadSize()));
	}
	return ret;
}

Void NSDevilX::CBinaryFileChunk::SChunkBase::_preWriteTo(VoidPtr & dst,Bool movePointer) const
{}

Void NSDevilX::CBinaryFileChunk::SChunkBase::_preWriteTo(CDataStreamWriter * writer) const
{
}

Boolean NSDevilX::CBinaryFileChunk::SChunkBase::_preReadFrom(VoidPtr & src,Bool movePointer)
{
	return true;
}

Boolean NSDevilX::CBinaryFileChunk::SChunkBase::_preReadFrom(CDataStreamReader * reader,Bool movePointer)
{
	return true;
}

NSDevilX::CBinaryFileChunk::STagChunk::STagChunk()
{
	memset(&mValue[0],0,mValue.size());
}

NSDevilX::CBinaryFileChunk::STagChunk::STagChunk(const String & tag)
{
	assert(tag.size()<=mValue.size());
	memset(&mValue[0],0,mValue.size());
	memcpy(&mValue[0],&tag[0],tag.size());
}

Boolean NSDevilX::CBinaryFileChunk::STagChunk::operator==(const STagChunk & chunk) const
{
	return mValue==chunk.mValue;
}

ConstVoidPtr NSDevilX::CBinaryFileChunk::STagChunk::_getWritePointer() const
{
	return &mValue[0];
}

UInt32 NSDevilX::CBinaryFileChunk::STagChunk::_getWriteSize() const
{
	return static_cast<UInt32>(mValue.size());
}

VoidPtr NSDevilX::CBinaryFileChunk::STagChunk::_getReadPointer()
{
	return &mValue[0];
}

UInt32 NSDevilX::CBinaryFileChunk::STagChunk::_getReadSize() const
{
	return static_cast<UInt32>(mValue.size());
}

NSDevilX::CBinaryFileChunk::SSizeChunk::SSizeChunk()
	:mSizeInBytes(0)
{}

NSDevilX::CBinaryFileChunk::SSizeChunk::SSizeChunk(UInt32 sizeInBytes)
	:mSizeInBytes(sizeInBytes)
{}

ConstVoidPtr NSDevilX::CBinaryFileChunk::SSizeChunk::_getWritePointer() const
{
	return &mSizeInBytes;
}

UInt32 NSDevilX::CBinaryFileChunk::SSizeChunk::_getWriteSize() const
{
	return sizeof(UInt32);
}

VoidPtr NSDevilX::CBinaryFileChunk::SSizeChunk::_getReadPointer()
{
	return &mSizeInBytes;
}

UInt32 NSDevilX::CBinaryFileChunk::SSizeChunk::_getReadSize() const
{
	return sizeof(UInt32);
}

NSDevilX::CBinaryFileChunk::SDataChunk::SDataChunk()
{}

NSDevilX::CBinaryFileChunk::SDataChunk::SDataChunk(ConstBytePtr data,UInt32 sizeInBytes)
{
	mData.resize(sizeInBytes);
	memcpy(&mData[0],data,sizeInBytes);
}

Void NSDevilX::CBinaryFileChunk::SDataChunk::_preWriteTo(VoidPtr & dst,Bool movePointer) const
{
	SSizeChunk size_chunk(static_cast<UInt32>(_getWriteSize()));
	size_chunk.writeTo(dst,movePointer);
}

Void NSDevilX::CBinaryFileChunk::SDataChunk::_preWriteTo(CDataStreamWriter * writer) const
{
	SSizeChunk size_chunk(static_cast<UInt32>(_getWriteSize()));
	size_chunk.writeTo(writer);
}

Boolean NSDevilX::CBinaryFileChunk::SDataChunk::_preReadFrom(VoidPtr & src,Bool movePointer)
{
	SSizeChunk size_chunk;
	Boolean ret=size_chunk.readFrom(src,movePointer);
	if(ret)
	{
		mData.resize(size_chunk.getValue());
	}
	return ret;
}

Boolean NSDevilX::CBinaryFileChunk::SDataChunk::_preReadFrom(CDataStreamReader * reader,Bool movePointer)
{
	SSizeChunk size_chunk;
	Boolean ret=size_chunk.readFrom(reader,movePointer);
	if(ret)
	{
		mData.resize(size_chunk.getValue());
	}
	return ret;
}

ConstVoidPtr NSDevilX::CBinaryFileChunk::SDataChunk::_getWritePointer() const
{
	return &mData[0];
}

UInt32 NSDevilX::CBinaryFileChunk::SDataChunk::_getWriteSize() const
{
	return static_cast<UInt32>(mData.size());
}

VoidPtr NSDevilX::CBinaryFileChunk::SDataChunk::_getReadPointer()
{
	return &mData[0];
}

UInt32 NSDevilX::CBinaryFileChunk::SDataChunk::_getReadSize() const
{
	return static_cast<UInt32>(mData.size());
}

NSDevilX::CBinaryFileChunk::SStringChunk::SStringChunk()
{}

NSDevilX::CBinaryFileChunk::SStringChunk::SStringChunk(const String & value)
	:SDataChunk(reinterpret_cast<ConstBytePtr>(&value[0]),static_cast<UInt32>(value.size()))
{}

const String NSDevilX::CBinaryFileChunk::SStringChunk::getValue() const
{
	return String(mData.begin(),mData.end());
}

const NSDevilX::CBinaryFileChunk::STagChunk NSDevilX::CBinaryFileChunk::msBegin("BEGIN");
const NSDevilX::CBinaryFileChunk::STagChunk NSDevilX::CBinaryFileChunk::msEnd("END");
NSDevilX::CBinaryFileChunk::CBinaryFileChunk()
{}

NSDevilX::CBinaryFileChunk::CBinaryFileChunk(const String & name,ConstBytePtr data,UInt32 sizeInBytes)
	:mName(name)
	,mData(data,sizeInBytes)
{
}

NSDevilX::CBinaryFileChunk::~CBinaryFileChunk()
{
}

Void NSDevilX::CBinaryFileChunk::writeTo(VoidPtr & dst,Bool movePointer) const
{
	msBegin.writeTo(dst,movePointer);
	mName.writeTo(dst,movePointer);
	mData.writeTo(dst,movePointer);
	msEnd.writeTo(dst,movePointer);
}

Void NSDevilX::CBinaryFileChunk::writeTo(CDataStreamWriter * writer)
{
	msBegin.writeTo(writer);
	mName.writeTo(writer);
	mData.writeTo(writer);
	msEnd.writeTo(writer);
}

Boolean NSDevilX::CBinaryFileChunk::readFrom(VoidPtr & src,Bool movePointer)
{
	STagChunk chunk;
	Boolean ret=chunk.readFrom(src,False);
	if(ret)
	{
		ret&=(msBegin==chunk);
		if(ret)
		{
			ret&=chunk.readFrom(src,movePointer);
			ret&=mName.readFrom(src,movePointer);
			ret&=mData.readFrom(src,movePointer);
			ret&=chunk.readFrom(src,movePointer);
			assert(msEnd==chunk);
		}
	}
	return ret;
}

Boolean NSDevilX::CBinaryFileChunk::readFrom(CDataStreamReader * reader,Bool movePointer)
{
	STagChunk chunk;
	Boolean ret=chunk.readFrom(reader,False);
	if(ret)
	{
		ret&=(msBegin==chunk);
		if(ret)
		{
			ret&=chunk.readFrom(reader,movePointer);
			ret&=mName.readFrom(reader,movePointer);
			ret&=mData.readFrom(reader,movePointer);
			ret&=chunk.readFrom(reader,movePointer);
			assert(msEnd==chunk);
		}
	}
	return ret;
}

NSDevilX::CBinaryFile::CBinaryFile()
{
	for(auto chunk:mChunks)
	{
		DEVILX_DELETE(chunk);
	}
}

Boolean NSDevilX::CBinaryFile::addChunk(const String & name,ConstBytePtr data,UInt32 sizeInBytes)
{
	Boolean ret=getChunk(name)?false:true;
	if(ret)
	{
		CBinaryFileChunk * chunk=DEVILX_NEW CBinaryFileChunk(name,data,sizeInBytes);
		mChunks.push_back(chunk);
	}
	return ret;
}

const CBinaryFileChunk * NSDevilX::CBinaryFile::getChunk(const String & name) const
{
	const CBinaryFileChunk * ret=nullptr;
	for(auto chunk:mChunks)
	{
		if(chunk->getName()==name)
		{
			ret=chunk;
			break;
		}
	}
	return ret;
}

Void NSDevilX::CBinaryFile::writeTo(CDataStream * dataStream)
{
	CDataStreamWriter * writer=dataStream->createWriter();
	for(auto chunk:mChunks)
	{
		chunk->writeTo(writer);
	}
	dataStream->destroyWrite(writer);
}

Boolean NSDevilX::CBinaryFile::readFrom(CDataStream * dataStream)
{
	for(auto chunk:mChunks)
	{
		DEVILX_DELETE(chunk);
	}
	mChunks.clear();
	CDataStreamReader * reader=dataStream->createReader();
	CBinaryFileChunk * chunk=DEVILX_NEW CBinaryFileChunk();
	Boolean ret=chunk->readFrom(reader,False);
	if(ret)
	{
		while(chunk->readFrom(reader))
		{
			mChunks.push_back(chunk);
			chunk=DEVILX_NEW CBinaryFileChunk();
		}
	}
	DEVILX_DELETE(chunk);
	return ret;
}