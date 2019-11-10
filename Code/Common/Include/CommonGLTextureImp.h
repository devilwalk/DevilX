#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLTextureImp
			:public ITexture
			,public CGLObject
		{
		protected:
		public:
			CGLTextureImp();
			virtual ~CGLTextureImp();
		};
	}
}