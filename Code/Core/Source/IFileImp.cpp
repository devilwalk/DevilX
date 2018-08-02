#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;

NSDevilX::NSCore::IFileImp::IFileImp(const CUTF8String & path)
	:mPath(path)
{

}

NSDevilX::NSCore::IFileImp::~IFileImp()
{

}

NSDevilX::NSCore::IDirectory * NSDevilX::NSCore::IFileImp::getDirectory() const
{
	return CFileManager::getSingleton().getDirectory(CUTF8String(CPathUtility::getParent(mPath)));
}

NSDevilX::CUTF8String NSDevilX::NSCore::IFileImp::getPath() const
{
	return mPath;
}

size_t NSDevilX::NSCore::IFileImp::getSize() const
{
	SizeT ret = 0;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	auto handle=::CreateFile(WString(mPath).c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
	LARGE_INTEGER size;
	if(!::GetFileSizeEx(handle,&size))
	{
		auto error=::GetLastError();
#ifdef _MSC_VER
		TString error_msg;
		error_msg.resize(4096);
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,nullptr,error,LANG_USER_DEFAULT,&error_msg[0],static_cast<DWORD>(error_msg.size()),nullptr);
		OutputDebugString(error_msg.c_str());
		return 0;
#endif
	}
	else
	{
		ret=static_cast<SizeT>(size.QuadPart);
	}
#else
	std::wifstream fs;
	fs.open(WString(mPath).c_str());
	if(fs.is_open())
	{
		return 0;
	}
	else
	{
		fs.seekg(0,std::ios::end);
		ret=fs.tellg();
		fs.close();
	}
#endif
	return ret;
}

NSDevilX::NSCore::IFileProcesser * NSDevilX::NSCore::IFileImp::retrieveProcesser()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void NSDevilX::NSCore::IFileImp::releaseProcesser(IFileProcesser * processer)
{
	throw std::logic_error("The method or operation is not implemented.");
}
