#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CModule
		{
		protected:
			const String mName;
			TMap<const String,CAny> mParameters;
		public:
			CModule(const String & name):mName(name){}
			virtual ~CModule(){}
			const String & getName()const
			{
				return mName;
			}
			Void setParameters(const String & name,const CAny & parameter)
			{
				mParameters[name]=parameter;
			}
			const CAny & getParameter(const String & name)const
			{
				return mParameters.find(name)->second;
			}
			virtual Void start()=0;
			virtual Void update()=0;
			virtual Void stop()
			{
				mParameters.clear();
			}
		};
	}
}