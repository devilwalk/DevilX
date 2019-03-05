#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGL
		{
			class IGAResourceImp
				:public IGAResource
			{
			protected:
				GLuint mInternal;
			public:
				IGAResourceImp();
				virtual~IGAResourceImp();
			};
			class IGPUBufferImp
				:public TBaseObject<IGPUBufferImp>
				,public IGAResourceImp
				,public IGABuffer
			{
			public:
				IGPUBufferImp();
				~IGPUBufferImp();
			};
		}
	}
}