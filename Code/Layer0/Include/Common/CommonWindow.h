#pragma once
#include "CommonType.h"
#include "CommonVectorI.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	class CDesktop
		:public TBaseObject<CDesktop>
	{
	public:
		CDesktop();
		~CDesktop();
		VoidPtr getHandle()const;
		CSInt2 getSize();
	};
	class CWindow
		:public TBaseObject<CWindow>
	{
	protected:
		VoidPtr mHandle;
		CSInt2 mPosition;
		CSInt2 mSize;
	public:
		CWindow();
		~CWindow();
		VoidPtr getHandle()const
		{
			return mHandle;
		}
		Void setPosition(const CSInt2 & position);
		const CSInt2 & getPosition()const
		{
			return mPosition;
		}
		Void setSize(const CSInt2 & size);
		const CSInt2 & getSize()const
		{
			return mSize;
		}
	};
}