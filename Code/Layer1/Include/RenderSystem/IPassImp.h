#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITechniqueImp;
		class IPassImp
			:public IPass
			,public TBaseObject<IPassImp>
		{
		protected:
			ITechniqueImp * const mTechnique;
		public:
			IPassImp(ITechniqueImp * technique);
			~IPassImp();
		};
	}
}