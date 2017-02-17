#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class IRenderMaterialImp
			:public TBaseObject<IRenderMaterialImp>
			,public IRenderMaterial
			,public CMessageNotifier
		{
		public:
			enum EMessage
			{
				EMessage_BeginColourChange,
				EMessage_EndColourChange
			};
		protected:
			const String & mName;
			CFloatRGBA mColour;
		public:
			IRenderMaterialImp(const String & name);
			~IRenderMaterialImp();
			virtual const String & getName() const override;
			virtual Void setColour(const CColour & colour) override;
			virtual const CColour & getColour() const override;
		};
	}
}