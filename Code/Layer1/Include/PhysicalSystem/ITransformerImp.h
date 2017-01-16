#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class ITransformerImp
			:public ITransformer
			,public TBaseObject<ITransformerImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginPositionChange,
				EMessage_EndPositionChange,
				EMessage_BeginOrientationChange,
				EMessage_EndOrientationChange,
				EMessage_BeginScaleChange,
				EMessage_EndScaleChange
			};
		protected:
			CFloat3 mPosition;
			CFloat4 mOrientation;
			CFloat3 mScale;
		public:
			ITransformerImp();
			~ITransformerImp();

			// Inherited via ITransformer
			virtual Void setPosition(DirectX::FXMVECTOR position) override;
			virtual const CFloat3 & getPosition() const override;
			virtual Void setOrientation(DirectX::FXMVECTOR orientation) override;
			virtual const CFloat4 & getOrientation() const override;
			virtual Void setScale(DirectX::FXMVECTOR scale) override;
			virtual const CFloat3 & getScale() const override;
		};
	}
}