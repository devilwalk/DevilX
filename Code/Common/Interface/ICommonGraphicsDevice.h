#pragma once
#include "ICommonGraphicsBuffer.h"
#include "ICommonGraphicsTexture.h"
#include "ICommonGraphicsInputLayout.h"
#include "ICommonGraphicsShader.h"
namespace NSDevilX
{
	class IGraphicsDevice
	{
	protected:
		virtual ~IGraphicsDevice(){}
	public:
		//d3d9 style
		virtual Bool createVertexBuffer(
			UINT                   length,
			DWORD                  usage,
			DWORD                  fvf,
			D3DPOOL                pool,
			OUT IGraphicsBuffer* buffer
		)=0;
		virtual Bool createIndexBuffer(
			UINT                  length,
			DWORD                 usage,
			D3DFORMAT             format,
			D3DPOOL               pool,
			OUT IGraphicsBuffer* buffer
		)=0;
		//d3d10/11 style
		virtual Bool createBuffer(const D3D10_BUFFER_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsBuffer* buffer)=0;
		virtual Bool createBuffer(const D3D11_BUFFER_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsBuffer* buffer)=0;
		//gl style
		virtual Bool createBufferData(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLenum usage,OUT IGraphicsBuffer* buffer)=0;
		virtual Bool createBufferStorage(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLbitfield flags,OUT IGraphicsBuffer* buffer)=0;
		//d3d9 style
		virtual Bool createTexture(UINT width,UINT height,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture)=0;
		virtual Bool createCubeTexture(UINT edageLength,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture)=0;
		virtual Bool createVolumeTexture(UINT width,UINT height,UINT depth,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture)=0;
		//d3d10/11 style
		virtual Bool createTexture1D(const D3D10_TEXTURE1D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture2D(const D3D10_TEXTURE2D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture3D(const D3D10_TEXTURE3D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture1D(const D3D11_TEXTURE1D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture2D(const D3D11_TEXTURE2D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture3D(const D3D11_TEXTURE3D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture)=0;
		//gl style
		virtual Bool createTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture2DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations,OUT IGraphicsTexture* texture)=0;
		virtual Bool createTexture3DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations,OUT IGraphicsTexture* texture)=0;
		virtual Bool createCompressedTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createCompressedTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)=0;
		virtual Bool createCompressedTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture)=0;
		//d3d9 style
		virtual Bool createVertexDeclaration(const D3DVERTEXELEMENT9* elements,OUT IGraphicsInputLayout* layout)=0;
		//d3d10/11 style
		virtual Bool createInputLayout(const D3D10_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IGraphicsInputLayout* layout)=0;
		virtual Bool createInputLayout(const D3D11_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IGraphicsInputLayout* layout)=0;
		//gl style
		virtual Bool vertexAttribFormat(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset,OUT IGraphicsInputLayout* layout)=0;
		virtual Bool vertexAttribIFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset,OUT IGraphicsInputLayout* layout)=0;
		virtual Bool vertexAttribPoint(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,ConstVoidPtr pointer,IGraphicsBuffer * buffer,OUT IGraphicsInputLayout* layout)=0;
		virtual Bool vertexAttribIPoint(GLuint index,GLint size,GLenum type,GLsizei stride,ConstVoidPtr pointer,IGraphicsBuffer* buffer,OUT IGraphicsInputLayout* layout)=0;
		//d3d style
		virtual Bool createVertexShader(ConstVoidPtr bytecoe,SizeT bytecodeSize,OUT IGraphicsShader* shader)=0;
		virtual Bool createPixelShader(ConstVoidPtr bytecoe,SizeT bytecodeSize,OUT IGraphicsShader* shader)=0;
		virtual Bool createGeometryShader(ConstVoidPtr bytecoe,SizeT bytecodeSize,OUT IGraphicsShader* shader)=0;
		virtual Bool createHullShader(ConstVoidPtr bytecoe,SizeT bytecodeSize,OUT IGraphicsShader* shader)=0;
		virtual Bool createDomainShader(ConstVoidPtr bytecoe,SizeT bytecodeSize,OUT IGraphicsShader* shader)=0;
		virtual Bool createComputeShader(ConstVoidPtr bytecoe,SizeT bytecodeSize,OUT IGraphicsShader* shader)=0;
		//gl style
		virtual Bool createShader(GLenum type,ConstVoidPtr bytecoe,SizeT bytecodeSize,OUT IGraphicsShader* shader)=0;
		virtual Bool attachProgram(GLenum type,IGraphicsShader* shader,OUT IGraphicsProgram* program)=0;
		virtual Bool linkProgram(OUT IGraphicsProgram* program)=0;
	};
}