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
			res->setDataStreamMT(DEVILX_NEW CMemoryStream(&stream));
			return true;
		}
	}
}