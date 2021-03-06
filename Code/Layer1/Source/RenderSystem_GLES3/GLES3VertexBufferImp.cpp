#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CVertexBufferImp::CVertexBufferImp(IVertexBufferImp * interfaceImp)
	:TInterfaceObject<IVertexBufferImp>(interfaceImp)
{
	RtlSecureZeroMemory(mBuffers,sizeof(mBuffers));
	_update();
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSGLES3::CVertexBufferImp::~CVertexBufferImp()
{
	for(auto buffer:mBuffers)
	{
		if(buffer)
		{
			glDeleteBuffers(1,&buffer);
			CUtility::checkGLError();
		}
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CVertexBufferImp::onMessage(IVertexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CVertexBufferImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CVertexBufferImp::_update()
{
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Count))
	{
		for(auto & vb:mBuffers)
		{
			if(vb)
			{
				glDeleteBuffers(1,&vb);
				CUtility::checkGLError();
				vb=0;
			}
		}
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Count);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Position)&&_update(CEnum::EVertexBufferType_Position))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Position);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Normal)&&_update(CEnum::EVertexBufferType_Normal))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Normal);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Tangent)&&_update(CEnum::EVertexBufferType_Tangent))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Tangent);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_TextureCoord0)&&_update(CEnum::EVertexBufferType_TextureCoord0))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_TextureCoord0);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_TextureCoord1)&&_update(CEnum::EVertexBufferType_TextureCoord1))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_TextureCoord1);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_BlendWeight)&&_update(CEnum::EVertexBufferType_BlendWeight))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_BlendWeight);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_BlendIndex)&&_update(CEnum::EVertexBufferType_BlendIndex))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_BlendIndex);
	}
	if(getInterfaceImp()->hasDirtyFlag(IVertexBufferImp::EDirtyFlag_Diffuse)&&_update(CEnum::EVertexBufferType_Diffuse))
	{
		getInterfaceImp()->removeDirtyFlag(IVertexBufferImp::EDirtyFlag_Diffuse);
	}
}

Bool NSDevilX::NSRenderSystem::NSGLES3::CVertexBufferImp::_update(CEnum::EVertexBufferType type)
{
	ConstVoidPtr data_ptr=nullptr;
	switch(type)
	{
	case CEnum::EVertexBufferType_Position:
		data_ptr=getInterfaceImp()->getPositions();
		break;
	case CEnum::EVertexBufferType_Normal:
		data_ptr=getInterfaceImp()->getNormals();
		break;
	case CEnum::EVertexBufferType_Tangent:
		data_ptr=getInterfaceImp()->getTangents();
		break;
	case CEnum::EVertexBufferType_TextureCoord0:
		data_ptr=getInterfaceImp()->getTextureCoords(IEnum::ETextureCoord_0);
		break;
	case CEnum::EVertexBufferType_TextureCoord1:
		data_ptr=getInterfaceImp()->getTextureCoords(IEnum::ETextureCoord_1);
		break;
	case CEnum::EVertexBufferType_BlendWeight:
		data_ptr=getInterfaceImp()->getBlendWeights();
		break;
	case CEnum::EVertexBufferType_BlendIndex:
		data_ptr=getInterfaceImp()->getBlendIndices();
		break;
	case CEnum::EVertexBufferType_Diffuse:
		data_ptr=getInterfaceImp()->getDiffuses();
		break;
	default:
		assert(0);
	}
	if(nullptr==data_ptr)
		return False;
	if(!getBuffers()[type])
	{
		GLuint buf=0;
		glGenBuffers(1,&buf);
		CUtility::checkGLError();
		if(GL_INVALID_VALUE!=buf)
		{
			glBindBuffer(GL_ARRAY_BUFFER,buf);
			CUtility::checkGLError();
			glBufferData(GL_ARRAY_BUFFER,CUtility::getStride(type)*getInterfaceImp()->getCount(),data_ptr,GL_STATIC_DRAW);
			CUtility::checkGLError();
			glBindBuffer(GL_ARRAY_BUFFER,0);
			CUtility::checkGLError();
		}
		else
		{
			buf=0;
		}
		mBuffers[type]=buf;
		notify(EMessage_BufferCreate,&type);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER,getBuffers()[type]);
		CUtility::checkGLError();
		glBufferSubData(GL_ARRAY_BUFFER,0,CUtility::getStride(type)*getInterfaceImp()->getCount(),data_ptr);
		CUtility::checkGLError();
		glBindBuffer(GL_ARRAY_BUFFER,0);
		CUtility::checkGLError();
	}
	return True;
}
