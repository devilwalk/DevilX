#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IColourUnitState
		{
		protected:
			virtual ~IColourUnitState(){}
		public:
			virtual Void setEnable(Bool enable)=0;
			virtual Bool getEnable()const=0;
			virtual Void setValue(const CColour & colour)=0;
			virtual const CColour & getValue()const=0;
		};
	}
}