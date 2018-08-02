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
		virtual Void setUserData(ConstCharPtr name,const CAny & userAny)=0;
		virtual Void setUserData(ConstVoidPtr key,const CAny & userAny)=0;
		virtual const CAny & getUserData(ConstCharPtr name)const=0;
		virtual const CAny & getUserData(ConstVoidPtr key)const=0;
		virtual Boolean hasUserData(ConstCharPtr name)const=0;
		virtual Boolean hasUserData(ConstVoidPtr key)const=0;
		virtual Void removeUserData(ConstCharPtr name)=0;
		virtual Void removeUserData(ConstVoidPtr key)=0;
	};
}