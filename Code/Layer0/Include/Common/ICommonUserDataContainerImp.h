#pragma once
#include "ICommonUserDataContainer.h"
#include "CommonUserDataContainer.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	class IUserDataContainerImp
		:public IUserDataContainer
		,public CUserDataContainer
	{
	public:
		IUserDataContainerImp(){}
		virtual ~IUserDataContainerImp()
		{
		}
		virtual Void setUserData(const String & name,const CAny & userAny)
		{
			CUserDataContainer::setUserData(name,userAny);
		}
		virtual Void setUserData(ConstVoidPtr key,const CAny & userAny)
		{
			CUserDataContainer::setUserData(key,userAny);
		}
		virtual const CAny & getUserData(const String & name)const
		{
			return CUserDataContainer::getUserData(name);
		}
		virtual const CAny & getUserData(ConstVoidPtr key)const
		{
			return CUserDataContainer::getUserData(key);
		}
		virtual Boolean hasUserData(const String & name)const
		{
			return CUserDataContainer::hasUserData(name);
		}
		virtual Boolean hasUserData(ConstVoidPtr key)const
		{
			return CUserDataContainer::hasUserData(key);
		}
		virtual Void removeUserData(const String & name)
		{
			CUserDataContainer::removeUserData(name);
		}
		virtual Void removeUserData(ConstVoidPtr key)
		{
			CUserDataContainer::removeUserData(key);
		}
	};
}
