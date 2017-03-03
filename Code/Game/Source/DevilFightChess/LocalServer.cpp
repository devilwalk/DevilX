#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CLocalServer::CLocalServer()
	:mDatabaseDirectory("LocalDatabase",DEVILX_NEW CDirectory(CDirectory::getApplicationDirectory()))
{
	if(!mDatabaseDirectory.getParent()->hasDirectory("LocalDatabase"))
	{
		mDatabaseDirectory.create();
	}
}

NSDevilX::NSFightChess::CLocalServer::~CLocalServer()
{
	DEVILX_DELETE(mDatabaseDirectory.getParent());
}

Void NSDevilX::NSFightChess::CLocalServer::userRegister(const String & name,const String & password,userRegisterCallback callback,VoidPtr userData)
{
	EReturnCode return_code=EReturnCode_Success;
	if((name==""))
	{
		return_code=EReturnCode_InvalidateUserName;
	}
	if((password==""))
	{
		return_code=EReturnCode_InvalidatePassword;
	}
	if(mDatabaseDirectory.hasDirectory(name))
	{
		return_code=EReturnCode_ExistUser;
	}
	if(EReturnCode_Success==return_code)
	{
		CDirectory user_database(name,&mDatabaseDirectory);
		user_database.create();
		CFileStream file_stream(user_database.getFullName()+"/information.db");
		CBinaryFile file;
		file.addChunk("Password",&password[0],static_cast<UInt32>(password.size()));
		file.writeTo(&file_stream);
	}
	callback(return_code,userData);
}

Void NSDevilX::NSFightChess::CLocalServer::userLogin(const String & name,const String & password,userLoginCallback callback,VoidPtr userData)
{
	EReturnCode return_code=EReturnCode_Success;
	if((name==""))
	{
		return_code=EReturnCode_InvalidateUserName;
	}
	if((password==""))
	{
		return_code=EReturnCode_InvalidatePassword;
	}
	if(!mDatabaseDirectory.hasDirectory(name))
	{
		return_code=EReturnCode_InvalidateUserName;
	}
	if(EReturnCode_Success==return_code)
	{
		CDirectory user_database(name,&mDatabaseDirectory);
		CFileStream file_stream(user_database.getFullName()+"/information.db");
		CBinaryFile file;
		file.readFrom(&file_stream);
		auto password_chunk=file.getChunk("Password");
		if(password_chunk->getDataInString()!=password)
		{
			return_code=EReturnCode_InvalidatePassword;
		}
	}
	callback(return_code,userData);
}
