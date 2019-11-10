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
			TMap<VoidPtr,GLint> mStateChangeOneParameters;
			TMap<VoidPtr,GLint[2]> mStateChangeTwoParameters;
			TMap<VoidPtr,GLint[3]> mStateChangeThreeParameters;
			TMap<VoidPtr,GLint[4]> mStateChangeFourParameters;
			TMap<VoidPtr,GLint[5]> mStateChangeFiveParameters;
		public:
			CGLStateImp();
			virtual ~CGLStateImp();
		};
	}
}