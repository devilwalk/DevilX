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
		virtual Void setUserData(ConstCharPtr name,const CAny & userAny) override
		{
			CUserDataContainer::setUserData(name,userAny);
		}
		virtual Void setUserData(ConstVoidPtr key,const CAny & userAny) override
		{
			CUserDataContainer::setUserData(key,userAny);
		}
		virtual const CAny & getUserData(ConstCharPtr name)const override
		{
			return CUserDataContainer::getUserData(name);
		}
		virtual const CAny & getUserData(ConstVoidPtr key)const override
		{
			return CUserDataContainer::getUserData(key);
		}
		virtual Boolean hasUserData(ConstCharPtr name)const override
		{
			return CUserDataContainer::hasUserData(name);
		}
		virtual Boolean hasUserData(ConstVoidPtr key)const override
		{
			return CUserDataContainer::hasUserData(key);
		}
		virtual Void removeUserData(ConstCharPtr name) override
		{
			CUserDataContainer::removeUserData(name);
		}
		virtual Void removeUserData(ConstVoidPtr key) override
		{
			CUserDataContainer::removeUserData(key);
		}
	};
}
