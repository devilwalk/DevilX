#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IColourUnitStateImp
			:public IColourUnitState
			,public TBaseObject<IColourUnitStateImp>
			,public CMessageNotifier
			,public CUserDataContainer
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
			Bool mEnable;
			CColour * mValue;
		public:
			IColourUnitStateImp(CColour::EType colourType=CColour::EType_RGBA);
			~IColourUnitStateImp();
			// Inherited via IColourUnitState
			virtual Void setEnable(Bool enable) override;
			virtual Bool getEnable() const override;
			virtual Void setValue(const CColour & colour) override;
			virtual const CColour & getValue() const override;
		};
	}
}