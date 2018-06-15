#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		template<class T>
		class TSingleton
		{
		protected:
			static T * msInstance;
		public:
			TSingleton()
			{
				assert(!msInstance);
				msInstance=static_cast<T*>(this);
			}
			virtual ~TSingleton()
			{
				assert(msInstance);
				msInstance=0;
			}
			static T & getSingleton()
			{
				assert(msInstance);
				return *msInstance;
			}
			static T * getSingletonPtr()
			{
				return msInstance;
			}
		};
		template<class T>
		T * TSingleton<T>::msInstance=0;

		template<class T>
		class TSingletonEx
		{
		protected:
			static T * msInstance;
		public:
			TSingletonEx()
			{
				assert(!msInstance);
				msInstance=static_cast<T*>(this);
			}
			virtual ~TSingletonEx()
			{
				assert(msInstance);
				msInstance=0;
			}
			static T & getSingleton()
			{
				if(!msInstance)
				{
					msInstance=new T;
				}
				return *msInstance;
			}
			static T * getSingletonPtr()
			{
				if(!msInstance)
				{
					msInstance=new T;
				}
				return msInstance;
			}
		};
		template<class T>
		T * TSingletonEx<T>::msInstance=0;
	}
}