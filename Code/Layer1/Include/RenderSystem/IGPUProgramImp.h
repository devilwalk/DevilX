#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGPUProgramImp
			:public IGPUProgram
			,public TBaseObject<IGPUProgramImp>
		{
		protected:
			const String mName;
		public:
			IGPUProgramImp(const String & name);
			~IGPUProgramImp();
		};
	}
}