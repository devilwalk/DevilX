#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IViewport;
		class IQuery
		{
		protected:
			virtual ~IQuery(){}
		public:
			virtual const String & getName()const=0;
			virtual IViewport * getViewport()const=0;
			virtual Void setArea(const CFloat2 & startPosition,const CFloat2 & endPosition)=0;
			virtual const CFloat2 & getStartPosition()const=0;
			virtual const CFloat2 & getEndPosition()const=0;
		};
	}
}