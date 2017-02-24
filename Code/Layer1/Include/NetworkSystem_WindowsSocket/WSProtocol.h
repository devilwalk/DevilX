#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		namespace NSWindowsSocket
		{
			class CProtocol
				:public TBaseObject<CProtocol>
			{
			public:
				struct SHead
				{
					UInt16 mDataSize;
				};
			protected:
				VoidPtr mData;
				Bool mNeedFree;
			public:
				CProtocol()
					:mData(nullptr)
					,mNeedFree(False)
				{}
				~CProtocol()
				{
					clear();
				}
				Void clear()
				{
					if(mNeedFree)
						DEVILX_FREE(mData);
					mData=nullptr;
				}
				Boolean parse(ConstVoidPtr buffer,SizeT sizeInBytes)
				{
					if((!buffer)||(!sizeInBytes))
						return false;
					mData=reinterpret_cast<VoidPtr>(reinterpret_cast<SizeT>(buffer));
					auto const send_size=getSendSizeInByts();
					if(send_size>sizeInBytes)
					{
						clear();
						return false;
					}
					return true;
				}
				Void setUserData(ConstVoidPtr data,UInt16 sizeInBytes)
				{
					DEVILX_FREE(mData);
					mData=DEVILX_ALLOC(sizeof(SHead)+sizeInBytes);
					static_cast<SHead*>(mData)->mDataSize=sizeInBytes;
					memcpy(static_cast<Byte*>(mData)+sizeof(SHead),data,sizeInBytes);
				}
				VoidPtr getUserData()const
				{
					return mData?static_cast<Byte*>(mData)+sizeof(SHead):0;
				}
				UInt16 getUserSizeInBytes()const
				{
					return mData?static_cast<SHead*>(mData)->mDataSize:0;
				}
				VoidPtr getSendData()const
				{
					return mData;
				}
				UInt32 getSendSizeInByts()
				{
					return getUserSizeInBytes()+sizeof(SHead);
				}
			};
		}
	}
}