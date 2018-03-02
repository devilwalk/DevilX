#pragma once
#include "CommonType.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CDataStream;
	class CDataStreamProcesser
	{
	protected:
		CDataStream * const mStream;
	protected:
		virtual ~CDataStreamProcesser();
	public:
		CDataStreamProcesser(CDataStream * stream);
		CDataStream * getStream()const{ return mStream; }
		virtual Boolean setPosition(UInt32 position)=0;
		virtual UInt32 getPosition()const=0;
		virtual Boolean move(Int32 offset)=0;
	};
	class CDataStreamReader
		:public CDataStreamProcesser
	{
	protected:
		virtual ~CDataStreamReader();
	public:
		CDataStreamReader(CDataStream * stream);
		virtual UInt32 process(UInt32 sizeInBytes,OUT VoidPtr dst)=0;
	};
	class CDataStreamWriter
		:public CDataStreamProcesser
	{
	protected:
		virtual ~CDataStreamWriter();
	public:
		CDataStreamWriter(CDataStream * stream);
		virtual UInt32 process(ConstVoidPtr src,UInt32 sizeInBytes)=0;
	};
	class CDataStream
	{
	public:
		CDataStream();
		virtual ~CDataStream();
		virtual CDataStreamReader * createReader()const=0;
		virtual Void destroyReader(CDataStreamReader * reader)const=0;
		virtual CDataStreamWriter * createWriter()const=0;
		virtual Void destroyWrite(CDataStreamWriter * writer)const=0;
		virtual void clear();
		virtual UInt32 getSize()const=0;
	};
}