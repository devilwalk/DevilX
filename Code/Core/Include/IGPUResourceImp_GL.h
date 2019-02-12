#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGL
		{
			class IGPUResourceImp
				:public IGPUResource
			{
			protected:
				GLuint mInternal;
			public:
				IGPUResourceImp();
				virtual~IGPUResourceImp();
			};
			class IGPUBufferImp
				:public TBaseObject<IGPUBufferImp>
				,public IGPUResourceImp
				,public IGPUBuffer
			{
			public:
				IGPUBufferImp();
				~IGPUBufferImp();
			};
		}
	}
}