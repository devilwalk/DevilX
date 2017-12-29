#include <Windows.h>
#include <string>
#include <vector>
#include <assert.h>
#include <set>
bool isVaild(const WIN32_FIND_DATAA & wfd)
{
	if(((wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==0)
		&&((std::string::npos!=std::string(wfd.cFileName).find(".sl"))||(std::string::npos!=std::string(wfd.cFileName).find(".hlsl"))||(std::string::npos!=std::string(wfd.cFileName).find(".glsl")))
		)
	{
		return true;
	}
	else
		return false;
}
std::vector<std::string> findFiles()
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
		if(isVaild(wfd))
			ret.push_back(dir+"\\"+wfd.cFileName);
		while(FindNextFileA(handle,&wfd))
		{
			if(isVaild(wfd))
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
void generatorHead(const std::vector<std::string> & files)
{
	std::string buf="#pragma once\r\nnamespace NSDevilX\r\n{\r\nnamespace NSRenderSystem\r\n{\r\nclass CDefinitionShader:public TBaseObject<CDefinitionShader>{\r\npublic:\r\n";
	for(auto const & file:files)
	{
		auto handle=CreateFileA(file.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,0,nullptr);
		std::string func_buf;
		func_buf.resize(GetFileSize(handle,nullptr));
		DWORD real=0;
		ReadFile(handle,&func_buf[0],static_cast<DWORD>(func_buf.size()),&real,nullptr);
		CloseHandle(handle);
		if((func_buf.find("main(")!=std::string::npos)||(func_buf.find("vsMain(")!=std::string::npos))
		{
			std::string function_name=file.substr(file.find_last_of("\\")+1);
			function_name=function_name.replace(function_name.find("."),1,1,'_');
			buf+="String "+function_name+";\r\n";
		}
	}
	buf+="CDefinitionShader();\r\n};\r\n}\r\n}";
	const std::string gen_head_dir=files.front().substr(0,files.front().find("\\Code\\"))+"\\Code\\Layer1\\Include\\Shader";
	const std::string gen_head_file_name="DefnitionShaderCodeFunction.h";
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
std::string processInclude(const std::vector<std::string> & functions,const std::vector<std::string> & functionNames,unsigned int index,std::vector<unsigned int> & includeStack,std::set<unsigned int> & includeSet)
{
	assert(std::find(includeStack.begin(),includeStack.end(),index)==includeStack.end());
	if(includeSet.find(index)!=includeSet.end())
		return std::string();
	includeSet.insert(index);
	includeStack.push_back(index);
	std::string ret=functions[index];
	while(std::string::npos!=ret.find("#include"))
	{
		auto include_left_index=ret.find_first_of("\"")+1;
		auto temp_text=ret.substr(include_left_index);
		auto include_right_index=include_left_index+temp_text.find_first_of("\"")-1;
		auto include=ret.substr(include_left_index,include_right_index-include_left_index+1);
		include=include.replace(include.find("."),1,1,'_');
		auto include_function_index=std::find(functionNames.begin(),functionNames.end(),include)-functionNames.begin();
		auto include_function=processInclude(functions,functionNames,static_cast<unsigned int>(include_function_index),includeStack,includeSet);
		std::string new_function;
		auto splite_index=ret.find("#include");
		if(splite_index>0)
			new_function=ret.substr(0,splite_index);
		new_function+=include_function;
		ret=ret.substr(include_right_index+2);
		new_function+=ret+"\r\n";
		ret=new_function;
	}
	includeStack.pop_back();
	return ret;
}
void generatorCpp(const std::vector<std::string> & files)
{
	std::string buf="#include \"Precompiler.h\"\r\nusing namespace NSDevilX;\r\nusing namespace NSRenderSystem;\r\nNSDevilX::NSRenderSystem::CDefinitionShader::CDefinitionShader()\r\n{\r\n";
	std::vector<std::string> function_names;
	std::vector<std::string> functions;
	for(auto const & file:files)
	{
		std::string function_name=file.substr(file.find_last_of("\\")+1);
		function_name=function_name.replace(function_name.find("."),1,1,'_');
		function_names.push_back(function_name);
		auto handle=CreateFileA(file.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,0,nullptr);
		std::string func_buf;
		func_buf.resize(GetFileSize(handle,nullptr));
		DWORD real=0;
		ReadFile(handle,&func_buf[0],static_cast<DWORD>(func_buf.size()),&real,nullptr);
		CloseHandle(handle);
		functions.push_back(func_buf);
	}
	std::vector<std::string> valid_functions;
	std::vector<std::string> valid_function_names;
	for(unsigned int i=0;i<functions.size();++i)
	{
		if((functions[i].find("main(")==std::string::npos)&&(functions[i].find("vsMain(")==std::string::npos))
			continue;
		std::vector<unsigned int> include_stack;
		std::set<unsigned int> include_set;
		auto func_buf=processInclude(functions,function_names,i,include_stack,include_set);
		std::string temp;
		while(func_buf.find("\r\n")!=std::string::npos)
		{
			temp+=func_buf.substr(0,func_buf.find_first_of("\r\n"))+"\\r\\n\"\r\n\"";
			func_buf=func_buf.substr(func_buf.find_first_of("\r\n")+2);
		}
		temp+=func_buf;
		func_buf=temp;
		//temp.clear();
		//while(func_buf.find("\"")!=std::string::npos)
		//{
		//	temp+=func_buf.substr(0,func_buf.find_first_of("\""))+"\\\"";
		//	func_buf=func_buf.substr(func_buf.find_first_of("\"")+1);
		//}
		//temp+=func_buf;
		//func_buf=temp;
		valid_functions.push_back(func_buf);
		valid_function_names.push_back(function_names[i]);
	}
	for(size_t i=0;i<valid_functions.size();++i)
	{
		buf+=valid_function_names[i]+"=\""+valid_functions[i]+"\";\r\n";
	}
	buf+="}";
	const std::string gen_cpp_dir=files.front().substr(0,files.front().find("\\Code\\"))+"\\Code\\Layer1\\Source\\Shader";
	const std::string gen_cpp_file_name="DefnitionShaderCodeFunction.cpp";
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
	auto files=findFiles();
	generatorHead(files);
	generatorCpp(files);
}