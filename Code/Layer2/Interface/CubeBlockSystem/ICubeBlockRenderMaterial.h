#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockSystem
	{
		class IRenderMaterial
		{
		protected:
			virtual ~IRenderMaterial(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setColour(const CColour & colour)=0;
			virtual const CColour & getColour()const=0;
		};
	}
}