#pragma once
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class IResource;
		class ILoadCallback
		{
		protected:
			virtual ~ILoadCallback(){}
		public:
			virtual Void onLoaded(IResource * resource)=0;
		};
		class IResource
		{
		protected:
			virtual ~IResource(){}
		public:
			virtual const String & getName()const=0;
			virtual const String & getFileName()const=0;
			virtual Void load(ILoadCallback * callback,Bool sync)=0;
			virtual Boolean isLoaded()const=0;
		};
	}
}