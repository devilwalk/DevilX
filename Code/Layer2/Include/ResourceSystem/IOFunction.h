#pragma once
#include "IResourceImp.h"
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		static Boolean IOFunction(VoidPtr parameter)
		{
			const auto res=static_cast<IResourceImp*>(parameter);
			auto const & file_name=res->getFileName();
			CFileStream stream(file_name);
			auto reader=stream.createReader();
			TVector<Byte> buf;
			buf.resize(stream.getSize());
			reader->process(stream.getSize(),&buf[0]);
			stream.destroyReader(reader);
			res->setBufferMT(buf);
		}
	}
}