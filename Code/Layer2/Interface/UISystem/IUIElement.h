#pragma once
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IElement
		{
		protected:
			virtual ~IElement(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setPosition(DirectX::FXMVECTOR positionVec)=0;
			virtual const CFloat3 & getPosition()const=0;
			virtual Void setSize(DirectX::FXMVECTOR sizeVec)=0;
			virtual const CFloat2 & getSize()const=0;
		};
	}
}