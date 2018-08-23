#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CLuaEngine::CLuaEngine(const String & filename)
	:mState(nullptr)
{
	mState=luaL_newstate();
	luaL_openlibs(mState);
	luaL_dofile(mState,filename.c_str());
}

NSDevilX::CLuaEngine::~CLuaEngine()
{
	lua_close(mState);
}

Void NSDevilX::CLuaEngine::registerFunction(const String & name,lua_CFunction function)
{
	lua_register(mState,name.c_str(),function);
}
