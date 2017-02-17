#include <Windows.h>
#include <string>
#include <vector>
bool isDir(const WIN32_FIND_DATAA & wfd)
{
	if((wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		&&(std::string::npos==std::string(wfd.cFileName).find("."))
		)
	{
		return true;
	}
	else
		return false;
}
std::vector<std::string> findDirs()
{
	std::vector<std::string> ret;
	char filename[MAX_PATH]={0};
	GetModuleFileNameA(NULL,filename,MAX_PATH);
	std::string dir=filename;
	dir=dir.substr(0,dir.find("\\DevilX")+7);
	dir+="\\Code\\Layer1\\Source\\Shader";
	WIN32_FIND_DATAA wfd;
	auto handle=FindFirstFileA((dir+"\\*").c_str(),&wfd);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		if(isDir(wfd))
			ret.push_back(dir+"\\"+wfd.cFileName);
		while(FindNextFileA(handle,&wfd))
		{
			if(isDir(wfd))
				ret.push_back(dir+"\\"+wfd.cFileName);
		}
	}
	FindClose(handle);
	return ret;
}
std::vector<std::string> findFiles(const std::string & dir,const std::string & ext)
{
	std::vector<std::string> ret;
	WIN32_FIND_DATAA wfd;
	auto handle=FindFirstFileA((dir+"\\*."+ext).c_str(),&wfd);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		ret.push_back(dir+"\\"+wfd.cFileName);
		while(FindNextFileA(handle,&wfd))
		{
			ret.push_back(dir+"\\"+wfd.cFileName);
		}
	}
	FindClose(handle);
	return ret;
}
void generatorHead(const std::vector<std::string> & files,const std::string & version)
{
	std::string buf="#pragma once\r\nnamespace NSDevilX\r\n{\r\nnamespace NSRenderSystem\r\n{\r\nnamespace NS"+version+"\r\n{\r\nclass CDefinitionShader:public TBaseObject<CDefinitionShader>{\r\npublic:\r\n";
	for(auto file:files)
	{
		std::string function_name=file.substr(file.find_last_of("\\")+1);
		function_name=function_name.replace(function_name.find("."),5,"");
		buf+="String "+function_name+";\r\n";
	}
	buf+="CDefinitionShader();\r\n};\r\n}\r\n}\r\n}";
	const std::string gen_head_dir=files.front().substr(0,files.front().find("\\Code\\"))+"\\Code\\Layer1\\Include\\Shader";
	const std::string gen_head_file_name=version+"DefnitionShaderCodeFunction.h";
	const std::string gen_head_full_name=gen_head_dir+"\\"+gen_head_file_name;
	std::string test_buf;
	DWORD real=0;
	auto handle=CreateFileA(gen_head_full_name.c_str(),GENERIC_READ,0,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		test_buf.resize(GetFileSize(handle,nullptr));
		ReadFile(handle,&test_buf[0],static_cast<DWORD>(test_buf.size()),&real,nullptr);
		CloseHandle(handle);
	}
	if(test_buf==buf)
		return;
	handle=CreateFileA(gen_head_full_name.c_str(),GENERIC_WRITE,0,nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
	WriteFile(handle,&buf[0],static_cast<DWORD>(buf.size()),&real,nullptr);
	CloseHandle(handle);
}
void generatorCpp(const std::vector<std::string> & files,const std::string & version)
{
	std::string buf="#include \"Precompiler.h\"\r\nusing namespace NSDevilX;\r\nusing namespace NSRenderSystem;\r\nusing namespace NS"+version+";\r\nNSDevilX::NSRenderSystem::NS"+version+"::CDefinitionShader::CDefinitionShader()\r\n{\r\n";
	std::vector<std::string> function_names;
	std::vector<std::string> functions;
	for(auto file:files)
	{
		std::string function_name=file.substr(file.find_last_of("\\")+1);
		function_name=function_name.replace(function_name.find("."),5,"");
		function_names.push_back(function_name);
		auto handle=CreateFileA(file.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,0,nullptr);
		std::string func_buf;
		func_buf.resize(GetFileSize(handle,nullptr));
		DWORD real=0;
		ReadFile(handle,&func_buf[0],static_cast<DWORD>(func_buf.size()),&real,nullptr);
		CloseHandle(handle);
		std::string temp;
		while(func_buf.find("\r\n")!=std::string::npos)
		{
			temp+=func_buf.substr(0,func_buf.find_first_of("\r\n"))+"\\r\\n\\\r\n";
			func_buf=func_buf.substr(func_buf.find_first_of("\r\n")+2);
		}
		temp+=func_buf;
		func_buf=temp;
		temp.clear();
		while(func_buf.find("\"")!=std::string::npos)
		{
			temp+=func_buf.substr(0,func_buf.find_first_of("\""))+"\\\"";
			func_buf=func_buf.substr(func_buf.find_first_of("\"")+1);
		}
		temp+=func_buf;
		func_buf=temp;
		functions.push_back(func_buf);
	}
	if(std::string::npos!=version.find("GLSL"))
	{
		bool has_include=false;
		do
		{
			has_include=false;
			for(auto & function:functions)
			{
				while(std::string::npos!=function.find("#include"))
				{
					auto include_left_index=function.find_first_of("\"")+1;
					auto temp_text=function.substr(include_left_index);
					auto include_right_index=include_left_index+temp_text.find_first_of("\"")-2;
					auto include=function.substr(include_left_index,include_right_index-include_left_index-5+1);
					auto include_function=functions[std::find(function_names.begin(),function_names.end(),include)-function_names.begin()];
					std::string new_function;
					auto splite_index=function.find("#include");
					if(splite_index>0)
						new_function=function.substr(0,splite_index);
					new_function+=include_function;
					new_function+=function.substr(include_right_index+3);
					function=new_function;
					has_include=true;
				}
			}
		}
		while(has_include);
	}
	for(size_t i=0;i<functions.size();++i)
	{
		buf+=function_names[i]+"=\""+functions[i]+"\";\r\n";
	}
	buf+="}";
	const std::string gen_cpp_dir=files.front().substr(0,files.front().find("\\Code\\"))+"\\Code\\Layer1\\Source\\Shader";
	const std::string gen_cpp_file_name=version+"DefnitionShaderCodeFunction.cpp";
	const std::string gen_cpp_full_name=gen_cpp_dir+"\\"+gen_cpp_file_name;
	std::string test_buf;
	DWORD real=0;
	auto handle=CreateFileA(gen_cpp_full_name.c_str(),GENERIC_READ,0,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
	if(INVALID_HANDLE_VALUE!=handle)
	{
		test_buf.resize(GetFileSize(handle,nullptr));
		ReadFile(handle,&test_buf[0],static_cast<DWORD>(test_buf.size()),&real,nullptr);
		CloseHandle(handle);
	}
	if(test_buf==buf)
		return;
	handle=CreateFileA(gen_cpp_full_name.c_str(),GENERIC_WRITE,0,nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
	WriteFile(handle,&buf[0],static_cast<DWORD>(buf.size()),&real,nullptr);
	CloseHandle(handle);
}
void main()
{
	auto dirs=findDirs();
	for(auto dir:dirs)
	{
		if(dir.find("\\HLSL5")!=std::string::npos)
		{
			auto files=findFiles(dir,"hlsl");
			generatorHead(files,"HLSL5");
			generatorCpp(files,"HLSL5");
		}
		else if(dir.find("\\HLSL4_1")!=std::string::npos)
		{
			auto files=findFiles(dir,"hlsl");
			generatorHead(files,"HLSL4_1");
			generatorCpp(files,"HLSL4_1");
		}
		else if(dir.find("\\GLSL4_5")!=std::string::npos)
		{
			auto files=findFiles(dir,"glsl");
			generatorHead(files,"GLSL4_5");
			generatorCpp(files,"GLSL4_5");
		}
	}
}