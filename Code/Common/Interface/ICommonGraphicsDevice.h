#pragma once
#include "ICommonGraphicsBuffer.h"
namespace NSDevilX
{
	class IGraphicsDevice
	{
	protected:
		virtual ~IGraphicsDevice(){}
	public:
		virtual IGraphicsVertexBuffer* CreateVertexBuffer(
			UINT                   Length,
			DWORD                  Usage,
			DWORD                  FVF,
			D3DPOOL                Pool
		)=0;
		virtual IGraphicsIndexBuffer* CreateIndexBuffer(
			UINT                  Length,
			DWORD                 Usage,
			D3DFORMAT             Format,
			D3DPOOL               Pool
		)=0;
		virtual IGraphicsBuffer* createBuffer(const D3D10_BUFFER_DESC* desc)=0;
		virtual IGraphicsBuffer* createBuffer(const D3D11_BUFFER_DESC* desc)=0;
	};
}