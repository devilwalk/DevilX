#pragma once
namespace NSDevilX
{
	namespace NSPhysicalSystem
	{
		class ITransformer
		{
		protected:
			virtual ~ITransformer(){}
		public:
			virtual Void setPosition(DirectX::FXMVECTOR position)=0;
			virtual const CFloat3 & getPosition()const=0;
			virtual Void setOrientation(DirectX::FXMVECTOR orientation)=0;
			virtual const CFloat4 & getOrientation()const=0;
			virtual Void setScale(DirectX::FXMVECTOR scale)=0;
			virtual const CFloat3 & getScale()const=0;
		};
	}
}