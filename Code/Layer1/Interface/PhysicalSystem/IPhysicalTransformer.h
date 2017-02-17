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
			virtual Void setPosition(const CFloat3 & position)=0;
			virtual const CFloat3 & getPosition()const=0;
			virtual Void setOrientation(const CFloat4 & orientation)=0;
			virtual const CFloat4 & getOrientation()const=0;
			virtual Void setScale(const CFloat3 & scale)=0;
			virtual const CFloat3 & getScale()const=0;
		};
	}
}