#pragma once
namespace NSDevilX
{
	namespace NSUISystem
	{
		class IElement
		{
		public:
			enum ECoord
			{
				ECoord_Local,
				ECoord_Parent
			};
		protected:
			virtual ~IElement(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setCoordParent(IElement * parent)=0;
			virtual IElement * getCoordParent()const=0;
			virtual Void setOrderParent(IElement * parent)=0;
			virtual IElement * getOrderParent()const=0;
			virtual Void setPosition(const CFloat2 & position)=0;
			virtual const CFloat2 & getPosition()const=0;
			virtual const CFloat2 & getDerivedPosition()const=0;
			virtual Void setSize(const CFloat2 & size)=0;
			virtual const CFloat2 & getSize()const=0;
			virtual const CFloat2 & getDerivedSize()const=0;
			virtual Void setOrder(Int32 order)=0;
			virtual Int32 getOrder()const=0;
			virtual Int32 getDerivedOrder()const=0;
			virtual CFloat2 convertSize(const CFloat2 & size,ECoord fromCoord,ECoord toCoord)const=0;
			virtual CFloat2 convertPosition(const CFloat2 & position,ECoord fromCoord,ECoord toCoord)const=0;
		};
	}
}