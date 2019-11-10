#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class ITexture
		{
		protected:
			virtual ~ITexture()
			{
			}
		};

		class IGraphicsTexture1D
		{
		protected:
			virtual ~IGraphicsTexture1D()
			{
			}
		public:
			virtual ITexture* queryInterface_IGraphicsTexture()const=0;
		};

		class IGraphicsTexture2D
		{
		protected:
			virtual ~IGraphicsTexture2D()
			{
			}
		public:
			virtual ITexture* queryInterface_IGraphicsTexture()const=0;
		};

		class IGraphicsTexture3D
		{
		protected:
			virtual ~IGraphicsTexture3D()
			{
			}
		public:
			virtual ITexture* queryInterface_IGraphicsTexture()const=0;
		};

		class IGraphicsTextureCube
		{
		protected:
			virtual ~IGraphicsTextureCube()
			{
			}
		public:
			virtual ITexture* queryInterface_IGraphicsTexture()const=0;
		};
	}
}