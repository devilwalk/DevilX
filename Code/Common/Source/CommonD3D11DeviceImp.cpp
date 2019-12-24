#include "Precompiler.h"
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
using namespace NSDevilX;

NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::CD3D11DeviceImp(ID3D11Device* internalDevice)
	:mInternal(internalDevice)
{
}

NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::~CD3D11DeviceImp()
{
}

Bool NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::createBufferPool(const TBufferPoolCreateInfos& createInfos,OUT IBufferPool* pool)
{
	Bool success=False;
	for(auto& create_info:createInfos)
	{
		D3D11_BUFFER_DESC desc={0};
		switch(create_info.mDescType)
		{
		case SBufferPoolCreateInfo::EDescType_D3D11:
		{
			desc=create_info.mD3D11Desc;
			success=True;
		}
		break;
		case SBufferPoolCreateInfo::EDescType_D3D10:
		{
			desc=*reinterpret_cast<const D3D11_BUFFER_DESC*>(&create_info.mD3D10Desc);
			success=True;
		}
		break;
		case SBufferPoolCreateInfo::EDescType_D3D9Vertex:
		{
			desc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
			desc.ByteWidth=create_info.mD3D9VertexDesc.mLength;
			desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE|((create_info.mD3D9VertexDesc.mUsage&D3DUSAGE_WRITEONLY)?0:D3D11_CPU_ACCESS_READ);
			desc.Usage=D3D11_USAGE_DEFAULT;
			success=True;
		}
		break;
		case SBufferPoolCreateInfo::EDescType_D3D9Index:
		{
			desc.BindFlags=D3D11_BIND_INDEX_BUFFER;
			desc.ByteWidth=create_info.mD3D9IndexDesc.mLength;
			desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE|((create_info.mD3D9VertexDesc.mUsage&D3DUSAGE_WRITEONLY)?0:D3D11_CPU_ACCESS_READ);
			desc.Usage=D3D11_USAGE_DEFAULT;
			success=True;
		}
		break;
		}
		if(success)
		{
			mInternal->CreateBuffer(&desc,nullptr,&static_cast<CD3D11BufferImp*>(pool)->mInternal);
		}
		if(success)
		{
			break;
		}
	}
	return success;
}

Bool NSDevilX::NSGraphicsAPI::CD3D11DeviceImp::createBuffer(const TBufferCreateInfos& createInfos,OUT IBuffer* buffer)
{
	Bool success=False;
	for(auto& create_info:createInfos)
	{
		if(create_info.mPoolInfo.mPool)
		{

		}
		else
		{
			D3D11_BUFFER_DESC desc={0};
			D3D11_SUBRESOURCE_DATA* init_data=nullptr;
			switch(create_info.mDescType)
			{
			case SBufferCreateInfo::EDescType_D3D12Committed:
			{
				desc.BindFlags=D3D11_BIND_VERTEX_BUFFER
					|D3D11_BIND_INDEX_BUFFER
					|((create_info.mD3D12CommittedDesc.mResourceDesc.Flags&D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS)?D3D11_BIND_UNORDERED_ACCESS:0)
					|((create_info.mD3D12CommittedDesc.mResourceDesc.Flags&D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE)?0:D3D11_BIND_SHADER_RESOURCE)
					|D3D11_BIND_STREAM_OUTPUT;
				desc.ByteWidth=create_info.mD3D12CommittedDesc.mResourceDesc.Width*create_info.mD3D12CommittedDesc.mResourceDesc.Height*create_info.mD3D12CommittedDesc.mResourceDesc.DepthOrArraySize;
				switch(create_info.mD3D12CommittedDesc.mHeapProperties.CPUPageProperty)
				{
				case D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE:
					desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
					break;
				case D3D12_CPU_PAGE_PROPERTY_WRITE_BACK:
					desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE|D3D11_CPU_ACCESS_READ;
					break;
				}
				if(create_info.mD3D12CommittedDesc.mHeapProperties.CPUPageProperty!=D3D12_CPU_PAGE_PROPERTY_NOT_AVAILABLE)
				{
					desc.Usage=D3D11_USAGE_DYNAMIC;
				}
				else
				{
					desc.Usage=D3D11_USAGE_DEFAULT;
				}
			}
			break;
			case SBufferCreateInfo::EDescType_D3D11:
			{
				desc=create_info.mD3D11Desc.mDesc;
				success=True;
			}
			break;
			case SBufferCreateInfo::EDescType_D3D10:
			{
				desc=*reinterpret_cast<const D3D11_BUFFER_DESC*>(&create_info.mD3D10Desc);
				success=True;
			}
			break;
			case SBufferCreateInfo::EDescType_D3D9Vertex:
			{
				desc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
				desc.ByteWidth=create_info.mD3D9VertexDesc.mLength;
				desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE|((create_info.mD3D9VertexDesc.mUsage&D3DUSAGE_WRITEONLY)?0:D3D11_CPU_ACCESS_READ);
				desc.Usage=D3D11_USAGE_DEFAULT;
				success=True;
			}
			break;
			case SBufferCreateInfo::EDescType_D3D9Index:
			{
				desc.BindFlags=D3D11_BIND_INDEX_BUFFER;
				desc.ByteWidth=create_info.mD3D9IndexDesc.mLength;
				desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE|((create_info.mD3D9VertexDesc.mUsage&D3DUSAGE_WRITEONLY)?0:D3D11_CPU_ACCESS_READ);
				desc.Usage=D3D11_USAGE_DEFAULT;
				success=True;
			}
			break;
			case SBufferCreateInfo::EDescType_GLCompatible:
			{
				switch(create_info.mGLCompatibleDesc.mTarget)
				{
				case GL_ARRAY_BUFFER:
					desc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
					break;
				case GL_ELEMENT_ARRAY_BUFFER:
					desc.BindFlags=D3D11_BIND_INDEX_BUFFER;
					break;
				case GL_UNIFORM_BUFFER:
					desc.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
					break;
				case GL_SHADER_STORAGE_BUFFER:
					desc.BindFlags=D3D11_BIND_UNORDERED_ACCESS;
					break;
				}
				desc.ByteWidth=create_info.mGLCompatibleDesc.mSize;
				switch(create_info.mGLCompatibleDesc.mUsage)
				{
				case GL_STATIC_DRAW:
				case GL_STATIC_COPY:
				case GL_STREAM_DRAW:
				case GL_STREAM_COPY:
				case GL_DYNAMIC_COPY:
					desc.Usage=D3D11_USAGE_DEFAULT;
					break;
				case GL_DYNAMIC_DRAW:
				case GL_DYNAMIC_READ:
					desc.Usage=D3D11_USAGE_DYNAMIC;
					break;
				case GL_STATIC_READ:
				case GL_STREAM_READ:
					desc.Usage=D3D11_USAGE_STAGING;
					break;
				}
			}
			break;
			}
			if(success)
			{
				mInternal->CreateBuffer(&desc,init_data,&static_cast<CD3D11BufferImp*>(buffer)->mInternal);
			}
		}
		if(success)
		{
			break;
		}
	}
	return success;
}

#endif