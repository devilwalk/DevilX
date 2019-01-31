#pragma once
namespace NSDevilX
{
	namespace NSGameEngine
	{
		class IObject
		{
		protected:
			virtual ~IObject()
			{
			}
		public:
			virtual const String & getName()const=0;
		};
	}
}