#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGL4;

NSDevilX::NSRenderSystem::NSGL4::CTexture2D::CTexture2D(ITexture2DImp * interfaceImp)
	:TInterfaceObject<ITexture2DImp>(interfaceImp)
{
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSGL4::CTexture2D::~CTexture2D()
{
}

Void NSDevilX::NSRenderSystem::NSGL4::CTexture2D::onMessage(ITexture2DImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
}

Void NSDevilX::NSRenderSystem::NSGL4::CTexture2D::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGL4::CTexture2D::_update()
{
	if((getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_ArraySize)
		||getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_Format)
		||getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_Mipmap)
		||getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_Size)
		)&&_recreateInternal()
		)
	{
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_ArraySize);
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_Format);
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_Mipmap);
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_Size);
	}
	if(getInterfaceImp()->hasDirtyFlag(ITexture2DImp::EDirtyFlag_Pixels)
		&&_updatePixels()
		)
	{
		getInterfaceImp()->removeDirtyFlag(ITexture2DImp::EDirtyFlag_Pixels);
	}
}

Boolean NSDevilX::NSRenderSystem::NSGL4::CTexture2D::_recreateInternal()
{
	glDeleteTextures(1,&mInternal);
	mInternal=0;
	if(getInterfaceImp()->getWidth()>0&&getInterfaceImp()->getHeight()>0)
	{
		GLint level_count=0;
		switch(getInterfaceImp()->getMipmapCount())
		{
		case 0xffffffff:
		{
			GLint row_level_count=1;
			auto width=getInterfaceImp()->getWidth();
			while(width>1)
			{
				row_level_count++;
				width/=2;
			}
			GLint col_level_count=1;
			auto height=getInterfaceImp()->getHeight();
			while(height>1)
			{
				col_level_count++;
				height/=2;
			}
			level_count=std::max<GLint>(row_level_count,col_level_count);
		}
		break;
		default:
			level_count=getInterfaceImp()->getMipmapCount()+1;
		}
		glGenTextures(1,&mInternal);
		glTextureStorage2D(GL_TEXTURE_2D,level_count,CMapper::mapping(getInterfaceImp()->getFormat()),getInterfaceImp()->getWidth(),getInterfaceImp()->getHeight());
		return true;
	}
	else
	{
		return false;
	}
}

Boolean NSDevilX::NSRenderSystem::NSGL4::CTexture2D::_updatePixels()
{
	if(getInternal())
	{
		GLint level_count=0;
		glGetTextureParameteriv(getInternal(),GL_TEXTURE_IMMUTABLE_LEVELS,&level_count);
		GLint texture_format=0;
		glGetTextureParameteriv(getInternal(),GL_TEXTURE_IMMUTABLE_FORMAT,&texture_format);
		for(GLint level=0;level<level_count;++level)
		{
			GLint width=0,height=0;
			glGetTextureLevelParameteriv(getInternal(),level,GL_TEXTURE_WIDTH,&width);
			glGetTextureLevelParameteriv(getInternal(),level,GL_TEXTURE_HEIGHT,&height);
			const auto row_pitch=CMapper::getRowPitch(texture_format,width);
			const auto depth_pitch=row_pitch*getInterfaceImp()->getHeight();
			auto pixels=static_cast<ConstBytePtr>(getInterfaceImp()->getPixels())+level*depth_pitch;
			switch(texture_format)
			{
			case GL_RGBA8:
			{
				DWORD * rgba=static_cast<DWORD*>(DEVILX_ALLOC(depth_pitch));
				for(UInt32 row=0,count=getInterfaceImp()->getHeight();row<count;++row)
				{
					memcpy(&rgba[(count-row-1)*row_pitch],pixels,row_pitch*sizeof(DWORD));
				}
				pixels=reinterpret_cast<ConstBytePtr>(rgba);
				glTextureSubImage2D(getInternal(),level,0,0,width,height,GL_RGBA8,GL_UNSIGNED_INT_8_8_8_8,pixels);
				DEVILX_FREE(const_cast<BytePtr>(pixels));
			}
			break;
			case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
			case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
			case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
				break;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
