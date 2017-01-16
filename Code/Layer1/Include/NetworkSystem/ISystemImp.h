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
				EMessage_PopUnprocessedLink,
				EMessage_Destruction,
				EMessage_Update
			};
		protected:
			Bool mExit;
			TNamedResourcePtrContainer<ILinkImp> mLinks;
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
			virtual ILink * createLink(const String & name,const String & destIP) override;
			virtual ILink * popUnprocessedLink(const String & name) override;
			virtual ILink * getLink(const String & name) const override;
			virtual Void destroyLink(ILink * link) override;
		};
	}
}