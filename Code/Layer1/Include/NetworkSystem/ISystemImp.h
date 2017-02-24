#pragma once
namespace NSDevilX
{
	namespace NSNetworkSystem
	{
		class ISystemImp
			:public ISystem
			,public TBaseObject<ISystemImp>
			,public CMessageNotifier
			,public TSingleton<ISystemImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginCreateLink,
				EMessage_EndCreateLink,
				EMessage_BeginDestroyLink,
				EMessage_EndDestroyLink,
				EMessage_Search,
				EMessage_Destruction,
				EMessage_Update
			};
		protected:
			Bool mExit;
			ISystemListener * mListener;
			TNamedResourcePtrMap<ILinkImp> mLinks;
		public:
			ISystemImp();
			~ISystemImp();
			Bool isExit()const
			{
				return mExit;
			}
			// Inherited via ISystem
			virtual Void shutdown() override;
			virtual Void update() override;
			virtual Void search(const String & destIP,UInt16 portStart=49152,UInt16 portEnd=-1) override;
			virtual ILink * createLink(const String & destIP,UInt16 port) override;
			virtual ILink * getLink(const String & destIP,UInt16 port) const override;
			virtual Void destroyLink(ILink * link) override;
			virtual Void setListener(ISystemListener * listener) override;
			virtual ISystemListener * getListener() const override;
		};
	}
}