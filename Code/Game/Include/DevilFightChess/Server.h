#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CServer
		{
		public:
			enum EReturnCode
			{
				EReturnCode_Success,
				EReturnCode_ExistUser,
				EReturnCode_InvalidateUserName,
				EReturnCode_InvalidatePassword
			};
			typedef Void(*userRegisterCallback)(EReturnCode,VoidPtr);
			typedef Void(*userLoginCallback)(EReturnCode,VoidPtr);
		protected:
		public:
			CServer(){}
			virtual ~CServer(){}
			virtual Void userRegister(const String & name,const String & password,userRegisterCallback callback,VoidPtr userData)=0;
			virtual Void userLogin(const String & name,const String & password,userLoginCallback callback,VoidPtr userData)=0;
		};
	}
}