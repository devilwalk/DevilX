#pragma once
#include "ICommonGroup.h"
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		struct SBufferPoolCreateInfo
		{
			struct SD3D9Vertex
			{
				UINT mLength;
				DWORD mUsage;
				DWORD mFVF;
				D3DPOOL mPool;
			};
			struct SD3D9Index
			{
				UINT mLength;
				DWORD mUsage;
				D3DFORMAT mFormat;
				D3DPOOL mPool;
			};
			struct SGLCompatible
			{
				GLenum mTarget;
				GLsizeiptr mSize;
				ConstVoidPtr mIntializeData;
				GLenum mUsage;
			};
			struct SGLStorage
			{
				GLenum mTarget;
				GLsizeiptr mSize;
				ConstVoidPtr mIntializeData;
				GLbitfield mFlags;
			};
			enum EDescType
			{
				EDescType_D3D12,
				EDescType_D3D11,
				EDescType_D3D10,
				EDescType_D3D9Vertex,
				EDescType_D3D9Index,
				EDescType_Vulkan,
				EDescType_GLCompatible,
				EDescType_GLStorage
			};
			union
			{
				D3D12_HEAP_DESC mD3D12Desc;
				D3D11_BUFFER_DESC mD3D11Desc;
				D3D10_BUFFER_DESC mD3D10Desc;
				SD3D9Vertex mD3D9VertexDesc;
				SD3D9Index mD3D9IndexDesc;
				VkMemoryAllocateInfo mVulkanDesc;
				SGLCompatible mGLCompatibleDesc;
				SGLStorage mGLStorageDesc;
			};
			EDescType mDescType;
		};
		typedef TVector<SBufferPoolCreateInfo> TBufferPoolCreateInfos;
		class IBufferPool
		{
		protected:
			virtual ~IBufferPool(){ }
		public:
		};
		struct SBufferCreateInfo
		{
			struct SPoolInfo
			{
				IBufferPool* mPool;
				UInt32 mOffset;
			};
			struct SD3D12Placed
			{
				UINT64 mHeapOffset;
				D3D12_RESOURCE_DESC mResourceDesc;
				D3D12_RESOURCE_STATES mInitialState;
				D3D12_CLEAR_VALUE* mOptimizedClearValue;
			};
			struct SD3D12Committed
			{
				D3D12_HEAP_PROPERTIES mHeapProperties;
				D3D12_HEAP_FLAGS mHeapFlags;
				D3D12_RESOURCE_DESC mResourceDesc;
				D3D12_RESOURCE_STATES mInitialState;
				D3D12_CLEAR_VALUE* mOptimizedClearValue;
			};
			struct SD3D11
			{
				D3D11_BUFFER_DESC mDesc;
				D3D11_SUBRESOURCE_DATA mInitializeData;
			};
			struct SD3D10
			{
				D3D10_BUFFER_DESC mDesc;
				D3D10_SUBRESOURCE_DATA mInitializeData;
			};
			struct SD3D9Vertex
			{
				UINT mLength;
				DWORD mUsage;
				DWORD mFVF;
				D3DPOOL mPool;
			};
			struct SD3D9Index
			{
				UINT mLength;
				DWORD mUsage;
				D3DFORMAT mFormat;
				D3DPOOL mPool;
			};
			struct SGLCompatible
			{
				GLenum mTarget;
				GLsizeiptr mSize;
				ConstVoidPtr mIntializeData;
				GLenum mUsage;
			};
			struct SGLStorage
			{
				GLenum mTarget;
				GLsizeiptr mSize;
				ConstVoidPtr mIntializeData;
				GLbitfield mFlags;
			};
			enum EDescType
			{
				EDescType_D3D12Placed,
				EDescType_D3D12Committed,
				EDescType_D3D11,
				EDescType_D3D10,
				EDescType_D3D9Vertex,
				EDescType_D3D9Index,
				EDescType_Vulkan,
				EDescType_GLCompatible,
				EDescType_GLStorage
			};
			union
			{
				SD3D12Placed mD3D12PlacedDesc;
				SD3D12Committed mD3D12CommittedDesc;
				SD3D11 mD3D11Desc;
				SD3D10 mD3D10Desc;
				SD3D9Vertex mD3D9VertexDesc;
				SD3D9Index mD3D9IndexDesc;
				VkBufferCreateInfo mVulkanDesc;
				SGLCompatible mGLCompatibleDesc;
				SGLStorage mGLStorageDesc;
			};
			EDescType mDescType;
			SPoolInfo mPoolInfo;
		};
		typedef TVector<SBufferCreateInfo> TBufferCreateInfos;
		class IBuffer
		{
		protected:
			virtual ~IBuffer()
			{
			}
		public:
		};
	}
}