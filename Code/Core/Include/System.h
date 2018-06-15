#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CSystem
			:public TSingletonEx<CSystem>
			,public TBaseObject<CSystem>
		{
		protected:
			ISystem*mSystem;
			IMemoryManager*mMemoryManager;
			IThreadManager*mThreadManager;
		public:
			CSystem();
			~CSystem();
			ISystem*getSystem()const{ return mSystem; }
			IMemoryManager*getMemoryManager()const{ return mMemoryManager; }
			IThreadManager*getThreadManager()const{ return mThreadManager; }
		};
	}
}