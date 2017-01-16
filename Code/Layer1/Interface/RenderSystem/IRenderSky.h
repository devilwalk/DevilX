#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISky
		{
		protected:
			virtual ~ISky(){}
		public:
			virtual Void setOrder(UInt32 order)=0;
			virtual UInt32 getOrder()const=0;
		};
	}
}