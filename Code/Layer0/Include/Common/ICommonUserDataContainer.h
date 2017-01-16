#pragma once
#include "CommonAny.h"
namespace NSDevilX
{
	class IUserDataContainer
	{
	protected:
		virtual ~IUserDataContainer()
		{
		}
	public:
		virtual Void setUserData(const String & name,const CAny & userAny)=0;
		virtual Void setUserData(ConstVoidPtr key,const CAny & userAny)=0;
		virtual const CAny & getUserData(const String & name)const=0;
		virtual const CAny & getUserData(ConstVoidPtr key)const=0;
		virtual Boolean hasUserData(const String & name)const=0;
		virtual Boolean hasUserData(ConstVoidPtr key)const=0;
	};
}