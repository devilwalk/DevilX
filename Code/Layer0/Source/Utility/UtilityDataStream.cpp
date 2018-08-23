#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CDataStreamProcesser::CDataStreamProcesser(CDataStream * stream)
	:mStream(stream)
{}

NSDevilX::CDataStreamProcesser::~CDataStreamProcesser()
{}

NSDevilX::CDataStreamReader::CDataStreamReader(CDataStream * stream)
	:CDataStreamProcesser(stream)
{}

NSDevilX::CDataStreamReader::~CDataStreamReader()
{}

NSDevilX::CDataStreamWriter::CDataStreamWriter(CDataStream * stream)
	:CDataStreamProcesser(stream)
{}

NSDevilX::CDataStreamWriter::~CDataStreamWriter()
{}

NSDevilX::CDataStream::CDataStream()
{}

NSDevilX::CDataStream::~CDataStream()
{}

void NSDevilX::CDataStream::clear()
{}
