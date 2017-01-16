#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableImp;
		class ISkyImp
			:public ISky
			,public TBaseObject<ISkyImp>
		{
		protected:
			IRenderableImp * const mRenderable;
			UInt32 mOrder;
		public:
			ISkyImp(IRenderableImp * renderable);
			~ISkyImp();

			// Inherited via ISky
			virtual Void setOrder(UInt32 order) override;
			virtual UInt32 getOrder() const override;
		};
	}
}