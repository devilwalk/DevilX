#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IElement
		{
		protected:
			virtual ~IElement(){}
		public:
			virtual Void setPosition(DirectX::FXMVECTOR positionVec)=0;
			virtual const CSInt2 & getPosition()const=0;
			virtual Void setSize(DirectX::FXMVECTOR sizeVec)=0;
			virtual const CSInt2 & getSize()const=0;
		};
	}
}