#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITextureUnitStateImp
			:public ITextureUnitState
			,public TBaseObject<ITextureUnitStateImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginTextureChange,
				EMessage_EndTextureChange
			};
		protected:
			IEnum::ETextureUnitStateType const mType;
			IMaterialImp * const mMaterial;
			ITexture * mTexture;
		public:
			ITextureUnitStateImp(IEnum::ETextureUnitStateType type,IMaterialImp * material);
			~ITextureUnitStateImp();

			// Inherited via ITextureUnitState
			virtual IEnum::ETextureUnitStateType getType() const override;
			virtual Void setTexture(ITexture * texture) override;
			virtual ITexture * getTexture() const override;
		};
	}
}