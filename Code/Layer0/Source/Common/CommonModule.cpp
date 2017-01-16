#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CModule::CModule(const String & fullName)
	:mInternalResource(0)
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	mInternalResource=::LoadLibraryA((fullName+".dll").c_str());
	auto proc=::GetProcAddress(reinterpret_cast<HMODULE>(mInternalResource),"dllLoad");
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
    mInternalResource=::dlopen((fullName+".so").c_str(),RTLD_LAZY);
	Void (*proc)();
	proc=reinterpret_cast<decltype(proc)>(::dlsym(mInternalResource,"dllLoad"));
#endif
	if(proc)
		proc();
}

NSDevilX::CModule::~CModule()
{
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	auto proc=::GetProcAddress(reinterpret_cast<HMODULE>(mInternalResource),"dllUnload");
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	Void (*proc)();
	proc=reinterpret_cast<decltype(proc)>(::dlsym(mInternalResource,"dllUnload"));
#endif
	if(proc)
		proc();
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	::FreeLibrary(reinterpret_cast<HMODULE>(mInternalResource));
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
    ::dlclose(mInternalResource);
#endif
}

CModule::ProAddress NSDevilX::CModule::getProcAddress(const String & name) const
{
	CModule::ProAddress ret=nullptr;
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
	ret=reinterpret_cast<decltype(ret)>(::GetProcAddress(reinterpret_cast<HMODULE>(mInternalResource),name.c_str()));
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
	ret=reinterpret_cast<decltype(ret)>(::dlsym(mInternalResource,name.c_str()));
#endif
	return ret;
}
