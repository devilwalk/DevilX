#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class ICommand
			{
			protected:
				virtual ~ICommand(){}
			public:
				virtual Boolean compile(Bool force=False)=0;
			};

			class ICommand_Clear
			{
			protected:
				virtual ~ICommand_Clear(){}
			public:
				virtual void setClearAttachments(UInt32 attachmentCount,const VkClearAttachment* attachments,UInt32 rectCount,const VkClearRect* rects)=0;
			};

			class ICommand_Draw
			{
			protected:
				virtual ~ICommand_Draw(){}
			public:
				virtual ICommand* queryInterface_ICommand()const=0;
				virtual Void setPipelineState(IGraphicsPipelineState* state)=0;
#if DEVILX_WINDOW_SYSTEM==DEVILX_WINDOW_SYSTEM_WINDOWS
				virtual Void setIndexBuffer(IBuffer* buffer,UInt32 offset,DXGI_FORMAT format)=0;
#endif
				virtual Void setVertexBuffers(UInt32 firstBinding,UInt32 count,const IBuffer** buffers,const VkDeviceSize* sizes)=0;
				virtual Void setIndexBuffer(IBuffer* buffer,VkDeviceSize offset,VkIndexType format)=0;
				virtual Void setDraw(UInt32 vertexCount,UInt32 instanceCount,UInt32 firstVertex,UInt32 firstInstance)=0;
				virtual Void setDrawIndexed(UInt32 indexCount,UInt32 instanceCount,UInt32 firstIndex,Int32 vertexOffset,UInt32 firstInstance)=0;
				virtual Void setDrawIndirect(IBuffer* buffer,VkDeviceSize offset,UInt32 drawCount,UInt32 stride)=0;
				virtual Void setDrawIndirectCount(IBuffer* buffer,VkDeviceSize offset,IBuffer* countBuffer,VkDeviceSize countBufferOffset,UInt32 maxDrawCount,UInt32 stride)=0;
				virtual Void setDrawIndexedIndirect(IBuffer* buffer,VkDeviceSize offset,UInt32 drawCount,UInt32 stride)=0;
				virtual Void setDrawIndexedIndirectCount(IBuffer* buffer,VkDeviceSize offset,IBuffer* countBuffer,VkDeviceSize countBufferOffset,UInt32 maxDrawCount,UInt32 stride)=0;
				virtual Void setDrawIndirectByteCount(UInt32 instanceCount,UInt32 firstInstance,IBuffer* counterBuffer,VkDeviceSize counterBufferOffset,UInt32 counterOffset,UInt32 vertexStride)=0;
			};

			class ICommand_Dispatch
			{
			protected:
				virtual ~ICommand_Dispatch(){}
			public:
				virtual ICommand* queryInterface_ICommand()const=0;
				virtual Void setPipelineState(IComputePipelineState* state)=0;
				virtual Void setDispatch(UInt32 groupCountX,UInt32 groupCountY,UInt32 groupCountZ)=0;
				virtual Void setDispatchIndirect(IBuffer* buffer,VkDeviceSize offset)=0;
				virtual Void setDispatchBase(UInt32 baseGroupX,UInt32 baseGroupY,UInt32 baseGroupZ,UInt32 groupCountX,UInt32 groupCountY,UInt32 groupCountZ)=0;
			};
		}
	}
}