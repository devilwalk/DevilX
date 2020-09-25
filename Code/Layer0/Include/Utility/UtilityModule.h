#pragma once
namespace NSDevilX
{
	class CModule
		:public TMemoryAllocatorObject<CModule>
	{
	public:
		typedef Void(*ProAddress)();
	protected:
		VoidPtr mInternalResource;
	public:
		CModule(const String & fullName);
		~CModule();
		ProAddress getProcAddress(const String & name)const;
	};
}