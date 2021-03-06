#include "Precompiler.h"
using namespace NSDevilX;

String NSDevilX::CDirectory::cleanPath(const String & path)
{
	String ret;
	auto path_copy=path;
	struct SReplace
	{
		Boolean operator()(const Char & c)
		{
			return c=='\\';
		}
	};
	std::replace_if(path_copy.begin(),path_copy.end(),SReplace(),'/');
	TList<String> dirs;
	while(String::npos!=path_copy.find('/'))
	{
		dirs.push_back(path_copy.substr(0,path_copy.find_first_of('/')));
		path_copy=path_copy.substr(path_copy.find_first_of('/')+1);
	}
	dirs.push_back(path_copy);
	for(auto iter=dirs.begin();dirs.end()!=iter;)
	{
		auto const & dir=*iter;
		if(dir=="..")
		{
			--iter;
			iter=dirs.erase(dirs.erase(iter));
		}
		else if(dir==".")
		{
			iter=dirs.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	SizeT index=0;
	for(auto const & dir:dirs)
	{
		ret+=dir+((index==dirs.size()-1)?"":"/");
		++index;
	}
	return ret;
}

String NSDevilX::CDirectory::getCurrentDirectory()
{
	String ret;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	ret.resize(MAX_PATH);
	::GetCurrentDirectoryA(MAX_PATH,&ret[0]);
	struct SReplace
	{
		Boolean operator()(const Char & c)
		{
			return c=='\\';
		}
	};
	std::replace_if(ret.begin(),ret.end(),SReplace(),'/');
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
	return ret.c_str();
}

String NSDevilX::CDirectory::getApplicationDirectory()
{
	String ret;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	ret.resize(MAX_PATH);
	::GetModuleFileNameA(nullptr,&ret[0],MAX_PATH);
	ret=ret.substr(0,ret.find_last_of('\\'));
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
	return cleanPath(ret.c_str());
}

String NSDevilX::CDirectory::getSystemFontsDirectory()
{
	String ret;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	ret.resize(MAX_PATH);
	::GetWindowsDirectoryA(&ret[0],MAX_PATH);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
	return cleanPath(ret.c_str())+"/Fonts";
}

String NSDevilX::CDirectory::getAbsolutePath(const String & path,String currentPath)
{
	String ret;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	if(String::npos!=path.find(':'))
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	if(path[0]=='/')
#endif
	{
		ret=cleanPath(path);
	}
	else
	{
		if(currentPath.empty())
		{
			currentPath=getCurrentDirectory();
		}
		ret=cleanPath(currentPath+"/"+path);
	}
	return ret;
}

Void NSDevilX::CDirectory::create(const String & fullName)
{
	String full_name=cleanPath(fullName);
	TVector<CDirectory*> dirs;
	while(String::npos!=full_name.find('/'))
	{
		dirs.push_back(DEVILX_NEW CDirectory(full_name.substr(0,full_name.find_first_of('/')),dirs.empty()?nullptr:dirs.back()));
		full_name=full_name.substr(full_name.find_first_of('/')+1);
	}
	dirs.push_back(DEVILX_NEW CDirectory(full_name,dirs.empty()?nullptr:dirs.back()));
	for(auto const & dir:dirs)
	{
		dir->create();
	}
	for(auto const & dir:dirs)
	{
		DEVILX_DELETE(dir);
	}
}

String NSDevilX::CDirectory::getDirectoryName(const String & name)
{
	auto clean_path=cleanPath(name);
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	WIN32_FIND_DATAA wfd;
	auto handle=::FindFirstFileA(clean_path.c_str(),&wfd);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		::FindClose(handle);
		if(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
			return clean_path;
	}
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
	auto index=clean_path.find_last_of('/');
	if(index!=String::npos)
	{
		clean_path=clean_path.substr(0,index);
	}
	else
	{
		clean_path="";
	}
	return clean_path;
}

String NSDevilX::CDirectory::getExtensionName(const String & name)
{
	auto pos=name.find_last_of('.');
	if(String::npos==pos)
		return "";
	else
	{
		auto ext=name.substr(pos+1);
		for(auto & c:ext)
		{
			c=tolower(c);
		}
		return ext;
	}
}

Boolean NSDevilX::CDirectory::hasDirectory(const String & name) const
{
	Boolean ret=false;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	String old_current_dir;
	old_current_dir.resize(MAX_PATH);
	::GetCurrentDirectoryA(MAX_PATH,&old_current_dir[0]);
	::SetCurrentDirectoryA(getFullName().c_str());
	WIN32_FIND_DATAA wfd;
	auto handle=::FindFirstFileA(name.c_str(),&wfd);
	if((INVALID_HANDLE_VALUE!=handle)&&(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
	{
		ret=true;
		::FindClose(handle);
	}
	::SetCurrentDirectoryA(old_current_dir.c_str());
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
	return ret;
}

Void NSDevilX::CDirectory::create()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	const auto full_name=getFullName();
	::CreateDirectoryA(full_name.c_str(),nullptr);
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}

Void NSDevilX::CDirectory::getChildFiles(TVector<String>& files) const
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	String old_current_dir;
	old_current_dir.resize(MAX_PATH);
	::GetCurrentDirectoryA(MAX_PATH,&old_current_dir[0]);
	::SetCurrentDirectoryA(getFullName().c_str());
	WIN32_FIND_DATAA wfd;
	auto handle=::FindFirstFileA("*",&wfd);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		do
		{
			if(!(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			{
				files.push_back(wfd.cFileName);
			}
		}
		while(::FindNextFileA(handle,&wfd));
		::FindClose(handle);
	}
	::SetCurrentDirectoryA(old_current_dir.c_str());
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#error("not implement!!")
#endif
}
