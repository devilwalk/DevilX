#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLBufferImp
			:public IBuffer
			,public CGLObject
		{
		protected:
		public:
			CGLBufferImp();
			virtual ~CGLBufferImp();
		};
	}
}