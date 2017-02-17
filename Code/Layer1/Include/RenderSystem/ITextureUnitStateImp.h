#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITextureUnitStateImp
			:public ITextureUnitState
			,public TBaseObject<ITextureUnitStateImp>
			,public CMessageNotifier
			,public CUserDataContainer
		{
		public:
			enum EMessage
			{
				EMessage_BeginTextureChange,
				EMessage_EndTextureChange
			};
		protected:
			ITexture * mTexture;
		public:
			ITextureUnitStateImp();
			~ITextureUnitStateImp();

			// Inherited via ITextureUnitState
			virtual Void setTexture(ITexture * texture) override;
			virtual ITexture * getTexture() const override;
		};
	}
}