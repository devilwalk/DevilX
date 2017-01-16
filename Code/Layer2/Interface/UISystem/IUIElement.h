#pragma once
#include "IUIEnum.h"
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
			virtual Void setPosition(DirectX::FXMVECTOR position)=0;
			virtual const CFloat2 & getPosition()const=0;
			virtual Void setRotation(const CRadian & rotation)=0;
			virtual const Radian & getRotation()const=0;
			virtual Void setScale(DirectX::FXMVECTOR size)=0;
			virtual const CFloat2 & getScale()const=0;
		};
	}
}