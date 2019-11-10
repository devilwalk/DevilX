#pragma once
#include "ICommonGraphicsAPIBuffer.h"
#include "ICommonGraphicsAPIHeap.h"
#include "ICommonGraphicsAPIInputLayout.h"
#include "ICommonGraphicsAPIPipelineState.h"
#include "ICommonGraphicsAPIShader.h"
#include "ICommonGraphicsAPITexture.h"
#include "ICommonGraphicsAPIVertexArrayObject.h"
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class IDevice
		{
		protected:
			virtual ~IDevice()
			{
			}
		public:
			//d3d9 style
			virtual Bool createVertexBuffer(
				UINT                   length,
				DWORD                  usage,
				DWORD                  fvf,
				D3DPOOL                pool,
				OUT IBuffer* buffer
			)=0;
			virtual Bool createIndexBuffer(
				UINT                  length,
				DWORD                 usage,
				D3DFORMAT             format,
				D3DPOOL               pool,
				OUT IBuffer* buffer
			)=0;
			//d3d10/11 style
			virtual Bool createBuffer(const D3D10_BUFFER_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IBuffer* buffer)=0;
			virtual Bool createBuffer(const D3D11_BUFFER_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IBuffer* buffer)=0;
			//gl style
			virtual Bool createBufferData(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLenum usage,OUT IBuffer* buffer)=0;
			virtual Bool createBufferStorage(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLbitfield flags,OUT IBuffer* buffer)=0;
			//d3d9 style
			virtual Bool createTexture(UINT width,UINT height,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture)=0;
			virtual Bool createCubeTexture(UINT edageLength,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture)=0;
			virtual Bool createVolumeTexture(UINT width,UINT height,UINT depth,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture)=0;
			//d3d10/11 style
			virtual Bool createTexture1D(const D3D10_TEXTURE1D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)=0;
			virtual Bool createTexture2D(const D3D10_TEXTURE2D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)=0;
			virtual Bool createTexture3D(const D3D10_TEXTURE3D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)=0;
			virtual Bool createTexture1D(const D3D11_TEXTURE1D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)=0;
			virtual Bool createTexture2D(const D3D11_TEXTURE2D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)=0;
			virtual Bool createTexture3D(const D3D11_TEXTURE3D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture)=0;
			//gl style
			virtual Bool createTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture)=0;
			virtual Bool createTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture)=0;
			virtual Bool createTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture)=0;
			virtual Bool createTexture2DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations,OUT ITexture* texture)=0;
			virtual Bool createTexture3DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations,OUT ITexture* texture)=0;
			virtual Bool createCompressedTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture)=0;
			virtual Bool createCompressedTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture)=0;
			virtual Bool createCompressedTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture)=0;
			//d3d9 style
			virtual Bool createVertexDeclaration(const D3DVERTEXELEMENT9* elements,OUT IInputLayout* layout)=0;
			//d3d10/11 style
			virtual Bool createInputLayout(const D3D10_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IInputLayout* layout)=0;
			virtual Bool createInputLayout(const D3D11_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IInputLayout* layout)=0;
			//gl style
			virtual Bool vertexAttribFormat(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset,OUT IInputLayout* layout)=0;
			virtual Bool vertexAttribIFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset,OUT IInputLayout* layout)=0;
			//gl style
			virtual Bool vertexAttribPoint(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,ConstVoidPtr pointer,IBuffer* buffer,OUT IVertexArrayObject* layout)=0;
			virtual Bool vertexAttribIPoint(GLuint index,GLint size,GLenum type,GLsizei stride,ConstVoidPtr pointer,IBuffer* buffer,OUT IVertexArrayObject* layout)=0;
			//d3d style
			virtual Bool createVertexShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)=0;
			virtual Bool createPixelShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)=0;
			virtual Bool createGeometryShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)=0;
			virtual Bool createHullShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)=0;
			virtual Bool createDomainShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)=0;
			virtual Bool createComputeShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader)=0;
			//gl style
			virtual Bool createShader(GLenum type,ConstCharPtr string,GLint length,OUT IShader* shader)=0;
			virtual Bool createShader(GLenum type,ConstCharPtr string,GLint length,OUT IProgram* shader)=0;
			virtual Bool createShader(GLenum type,GLenum binaryFormat,ConstVoidPtr bytecode,GLsizei bytecodeSize,OUT IShader* shader)=0;
			virtual Bool createShader(GLenum type,GLenum binaryFormat,ConstVoidPtr bytecode,GLsizei bytecodeSize,OUT IProgram* shader)=0;
			virtual Bool attachProgram(GLenum type,IShader* shader,OUT IProgram* program)=0;
			virtual Bool linkProgram(OUT IProgram* program)=0;
			//d3d10/11 style
			virtual Bool createBlendState(const D3D10_BLEND_DESC& desc,OUT IBlendState* state)=0;
			virtual Bool createBlendState(const D3D10_BLEND_DESC1& desc,OUT IBlendState* state)=0;
			virtual Bool createBlendState(const D3D11_BLEND_DESC& desc,OUT IBlendState* state)=0;
			virtual Bool createBlendState(const D3D11_BLEND_DESC1& desc,OUT IBlendState* state)=0;
			//d3d10/11 style
			virtual Bool createDepthStencilState(const D3D10_DEPTH_STENCIL_DESC& desc,OUT IDepthStencilState* state)=0;
			virtual Bool createDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& desc,OUT IDepthStencilState* state)=0;
			//d3d10/11 style
			virtual Bool createRasterizerState(const D3D10_RASTERIZER_DESC& desc,OUT IRasterizerState* state)=0;
			virtual Bool createRasterizerState(const D3D11_RASTERIZER_DESC& desc,OUT IRasterizerState* state)=0;
			virtual Bool createRasterizerState(const D3D11_RASTERIZER_DESC1& desc,OUT IRasterizerState* state)=0;
			virtual Bool createRasterizerState(const D3D11_RASTERIZER_DESC2& desc,OUT IRasterizerState* state)=0;
		};
	}
}