#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CModule
		{
		protected:
			const String mName;
		public:
			CModule(const String & name):mName(name){}
			virtual ~CModule(){}
			const String & getName()const
			{
				return mName;
			}
			virtual Void start()=0;
			virtual Void update()=0;
			virtual Void stop()=0;
		};
	}
}