#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;
using namespace NSGLES3;

NSDevilX::NSRenderSystem::NSGLES3::CIndexBufferImp::CIndexBufferImp(IIndexBufferImp * interfaceImp)
	:TInterfaceObject<IIndexBufferImp>(interfaceImp)
	,mBuffer(0)
{
	_update();
	CSystemImp::getSingleton().addListener(static_cast<TMessageReceiver<CSystemImp>*>(this),CSystemImp::EMessage_BeginFrame);
}

NSDevilX::NSRenderSystem::NSGLES3::CIndexBufferImp::~CIndexBufferImp()
{
	if(getBuffer())
	{
		glDeleteBuffers(1,&mBuffer);
		CUtility::checkGLError();
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CIndexBufferImp::onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	return Void();
}

Void NSDevilX::NSRenderSystem::NSGLES3::CIndexBufferImp::onMessage(CSystemImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess)
{
	switch(message)
	{
	case CSystemImp::EMessage_BeginFrame:
		_update();
		break;
	}
}

Void NSDevilX::NSRenderSystem::NSGLES3::CIndexBufferImp::_update()
{
	if(getInterfaceImp()->hasDirtyFlag(IIndexBufferImp::EDirtyFlag_Count))
	{
		if(getBuffer())
		{
			glDeleteBuffers(1,&mBuffer);
			CUtility::checkGLError();
			mBuffer=0;
		}
		getInterfaceImp()->removeDirtyFlag(IIndexBufferImp::EDirtyFlag_Count);
	}
	if(getInterfaceImp()->hasDirtyFlag(IIndexBufferImp::EDirtyFlag_Index))
	{
		if(getInterfaceImp()->getIndices())
		{
			if(!getBuffer())
			{
				GLuint buf=0;
				glCreateBuffers(1,&buf);
				CUtility::checkGLError();
				if(GL_INVALID_VALUE!=buf)
				{
					glNamedBufferStorage(buf,sizeof(UInt32)*getInterfaceImp()->getCount(),getInterfaceImp()->getIndices(),GL_DYNAMIC_STORAGE_BIT);
					CUtility::checkGLError();
				}
				else
				{
					buf=0;
				}
				mBuffer=buf;
				notify(EMessage_BufferCreate);
			}
			else
			{
				glNamedBufferSubData(getBuffer(),0,sizeof(UInt32)*getInterfaceImp()->getCount(),getInterfaceImp()->getIndices());
				CUtility::checkGLError();
			}
			getInterfaceImp()->removeDirtyFlag(IIndexBufferImp::EDirtyFlag_Index);
		}
	}
}
