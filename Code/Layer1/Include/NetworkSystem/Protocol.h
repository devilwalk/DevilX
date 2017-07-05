#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class CProtocol
			:public TBaseObject<CProtocol>
		{
		public:
			struct SHead
			{
				UInt32 mDataSize;
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
			Void parse(ConstVoidPtr & buffer)
			{
				if(!buffer)
					return;
				mData=reinterpret_cast<VoidPtr>(reinterpret_cast<SizeT>(buffer));
				assert(getUserSizeInBytes()>0);
				auto const send_size=getSendSizeInBytes();
				buffer=reinterpret_cast<ConstVoidPtr>(reinterpret_cast<SizeT>(buffer)+send_size);
			}
			Void setUserData(ConstVoidPtr data,UInt32 sizeInBytes)
			{
				assert(data&&(sizeInBytes>0));
				DEVILX_FREE(mData);
				mData=DEVILX_ALLOC(sizeof(SHead)+sizeInBytes);
				static_cast<SHead*>(mData)->mDataSize=sizeInBytes;
				memcpy(static_cast<Byte*>(mData)+sizeof(SHead),data,sizeInBytes);
			}
			ConstVoidPtr getUserData()const
			{
				return mData?static_cast<Byte*>(mData)+sizeof(SHead):0;
			}
			UInt32 getUserSizeInBytes()const
			{
				return mData?static_cast<SHead*>(mData)->mDataSize:0;
			}
			ConstVoidPtr getSendData()const
			{
				return mData;
			}
			UInt32 getSendSizeInBytes()
			{
				return getUserSizeInBytes()+sizeof(SHead);
			}
		};
	}
}