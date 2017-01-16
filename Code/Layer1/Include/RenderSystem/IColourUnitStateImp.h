#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IMaterialImp;
		class IColourUnitStateImp
			:public IColourUnitState
			,public TBaseObject<IColourUnitStateImp>
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginEnableChange,
				EMessage_EndEnableChange,
				EMessage_BeginValueChange,
				EMessage_EndValueChange
			};
		protected:
			const IEnum::EColourUnitStateType mType;
			IMaterialImp * const mMaterial;
			Bool mEnable;
			CColour mValue;
		public:
			IColourUnitStateImp(IEnum::EColourUnitStateType type,IMaterialImp * material);
			~IColourUnitStateImp();
			// Inherited via IColourUnitState
			virtual IEnum::EColourUnitStateType getType() const override;
			virtual Void setEnable(Bool enable) override;
			virtual Bool getEnable() const override;
			virtual Void setValue(const CColour & colour) override;
			virtual const CColour & getValue() const override;
		};
	}
}