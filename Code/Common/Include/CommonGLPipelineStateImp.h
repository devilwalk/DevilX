#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLStateImp
			:public IBlendState
			,public IDepthStencilState
			,public IRasterizerState
		{
			friend class CGLDeviceImp;
		protected:
			TMap<VoidPtr,GLint> mStateChangeParameters_I;
			TMap<VoidPtr,GLint[2]> mStateChangeParameters_II;
			TMap<VoidPtr,GLint[3]> mStateChangeParameters_III;
			TMap<VoidPtr,GLint[4]> mStateChangeParameters_IIII;
			TMap<VoidPtr,GLint[5]> mStateChangeParameters_IIIII;
			TMap<VoidPtr,GLfloat> mStateChangeParameters_F;
			TMap<VoidPtr,GLfloat[2]> mStateChangeParameters_FF;
			TMap<VoidPtr,GLfloat[3]> mStateChangeParameters_FFF;
		public:
			CGLStateImp();
			virtual ~CGLStateImp();
		};
	}
}