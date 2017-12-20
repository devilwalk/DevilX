#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		template<class T>
		class IRefValueUnitStateT
		{
		protected:
			virtual ~IRefValueUnitStateT(){}
		public:
			virtual Void setEnable(Bool enable)=0;
			virtual Bool getEnable()const=0;
			virtual Void setValue(const T & value)=0;
			virtual const T & getValue()const=0;
		};
		typedef IRefValueUnitStateT<CColour> IColourUnitState;
		template<typename T>
		class IValueUnitStateT
		{
		protected:
			virtual ~IValueUnitStateT(){}
		public:
			virtual Void setEnable(Bool enable)=0;
			virtual Bool getEnable()const=0;
			virtual Void setValue(T value)=0;
			virtual T getValue()const=0;
		};
		typedef IValueUnitStateT<Float> IFloatUnitState;
	}
}