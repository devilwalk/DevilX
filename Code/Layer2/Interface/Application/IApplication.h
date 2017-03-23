#pragma once
namespace NSDevilX
{
	namespace NSApplication
	{
		class IApplication
		{
		protected:
			virtual ~IApplication(){}
		public:
			virtual CWindow * getWindow()const=0;
			virtual Void run()=0;
			virtual Void shutdown()=0;
		};
		IApplication * getApp();
	}
}