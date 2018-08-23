#pragma once
namespace NSDevilX
{
	class CLuaEngine
	{
	protected:
		lua_State * mState;
	public:
		CLuaEngine(const String & filename);
		~CLuaEngine();
		Void registerFunction(const String & name,lua_CFunction function);
	};
}