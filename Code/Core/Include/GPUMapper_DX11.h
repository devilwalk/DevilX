#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSDX11
		{
			class CMapper
			{
			public:
				static D3D11_USAGE mapping(IGPUEnum::EUsage usage)
				{
					switch(usage)
					{
					case IGPUEnum::EUsage_DEFAULT:return D3D11_USAGE_DEFAULT;
					case IGPUEnum::EUsage_DYNAMIC:return D3D11_USAGE_DYNAMIC;
					case IGPUEnum::EUsage_IMMUTABLE:return D3D11_USAGE_IMMUTABLE;
					case IGPUEnum::EUsage_STAGING:return D3D11_USAGE_STAGING;
					default:
						return D3D11_USAGE_DEFAULT;
					}
				}
				static D3D11_BUFFER_DESC & mapping(const IGPUStruct::SBufferDesc & src,D3D11_BUFFER_DESC & dest)
				{
					dest.BindFlags=src.BindFlags;
					dest.ByteWidth=src.ByteWidth;
					dest.CPUAccessFlags=src.CPUAccessFlags;
					dest.MiscFlags=src.MiscFlags;
					dest.StructureByteStride=src.StructureByteStride;
					dest.Usage=mapping(src.Usage);
					return dest;
				}
				static D3D11_BUFFER_DESC mapping(const IGPUStruct::SBufferDesc & src)
				{
					D3D11_BUFFER_DESC ret={};
					return mapping(src,ret);
				}
				static D3D11_SUBRESOURCE_DATA & mapping(const IGPUStruct::SSubResourceData & src,D3D11_SUBRESOURCE_DATA & dest)
				{
					dest.pSysMem=src.pSysMem;
					dest.SysMemPitch=src.SysMemPitch;
					dest.SysMemSlicePitch=src.SysMemSlicePitch;
					return dest;
				}
				static D3D11_SUBRESOURCE_DATA mapping(const IGPUStruct::SSubResourceData & src)
				{
					D3D11_SUBRESOURCE_DATA ret={};
					return mapping(src,ret);
				}
			};
		}
	}
}