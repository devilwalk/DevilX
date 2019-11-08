#pragma once
namespace NSDevilX
{
	class IGraphicsTexture
	{
	protected:
		virtual ~IGraphicsTexture(){ }
	};

	class IGraphicsTexture1D
	{
	protected:
		virtual ~IGraphicsTexture1D()
		{
		}
	public:
		virtual IGraphicsTexture* queryInterface_IGraphicsTexture()const=0;
	};

	class IGraphicsTexture2D
	{
	protected:
		virtual ~IGraphicsTexture2D()
		{
		}
	public:
		virtual IGraphicsTexture* queryInterface_IGraphicsTexture()const=0;
	};

	class IGraphicsTexture3D
	{
	protected:
		virtual ~IGraphicsTexture3D()
		{
		}
	public:
		virtual IGraphicsTexture* queryInterface_IGraphicsTexture()const=0;
	};

	class IGraphicsTextureCube
	{
	protected:
		virtual ~IGraphicsTextureCube()
		{
		}
	public:
		virtual IGraphicsTexture* queryInterface_IGraphicsTexture()const=0;
	};
}