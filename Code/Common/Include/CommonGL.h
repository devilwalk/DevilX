#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLObject
		{
			friend class CGLDeviceImp;
		protected:
			GLuint mInternal;
		public:
			CGLObject();
			virtual ~CGLObject();
		};
	}
}