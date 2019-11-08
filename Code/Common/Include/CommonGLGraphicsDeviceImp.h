#pragma once
namespace NSDevilX
{
	class CGLGraphicsDeviceImp
		:public IGraphicsDevice
	{
	protected:
	public:
		CGLGraphicsDeviceImp();
		virtual ~CGLGraphicsDeviceImp();

		// 通过 IGraphicsDevice 继承
		virtual Bool createVertexBuffer(UINT length,DWORD usage,DWORD fvf,D3DPOOL pool,OUT IGraphicsBuffer* buffer) override;
		virtual Bool createIndexBuffer(UINT length,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsBuffer* buffer) override;
		virtual Bool createBuffer(const D3D10_BUFFER_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsBuffer* buffer) override;
		virtual Bool createBuffer(const D3D11_BUFFER_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsBuffer* buffer) override;

		// 通过 IGraphicsDevice 继承
		virtual Bool createBufferData(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLenum usage,OUT IGraphicsBuffer* buffer) override;
		virtual Bool createBufferStorage(GLenum target,GLsizeiptr size,ConstVoidPtr intializeData,GLbitfield flags,OUT IGraphicsBuffer* buffer) override;
		virtual Bool createTexture(UINT width,UINT height,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture) override;
		virtual Bool createCubeTexture(UINT edageLength,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture) override;
		virtual Bool createVolumeTexture(UINT width,UINT height,UINT depth,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture1D(const D3D10_TEXTURE1D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture2D(const D3D10_TEXTURE2D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture3D(const D3D10_TEXTURE3D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture1D(const D3D11_TEXTURE1D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture2D(const D3D11_TEXTURE2D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture3D(const D3D11_TEXTURE3D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture2DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations,OUT IGraphicsTexture* texture) override;
		virtual Bool createTexture3DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations,OUT IGraphicsTexture* texture) override;
		virtual Bool createCompressedTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createCompressedTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture) override;
		virtual Bool createCompressedTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT IGraphicsTexture* texture) override;

		// 通过 IGraphicsDevice 继承
		virtual Bool createVertexDeclaration(const D3DVERTEXELEMENT9* elements,OUT IGraphicsInputLayout* layout) override;
		virtual Bool createInputLayout(const D3D10_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IGraphicsInputLayout* layout) override;
		virtual Bool createInputLayout(const D3D11_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IGraphicsInputLayout* layout) override;
		virtual Bool vertexAttribFormat(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset,OUT IGraphicsInputLayout* layout) override;
		virtual Bool vertexAttribIFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset,OUT IGraphicsInputLayout* layout) override;
		virtual Bool vertexAttribPoint(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,ConstVoidPtr pointer,OUT IGraphicsInputLayout* layout) override;
		virtual Bool vertexAttribIPoint(GLuint index,GLint size,GLenum type,GLsizei stride,ConstVoidPtr pointer,OUT IGraphicsInputLayout* layout) override;
	};

	class CGLES2GraphicsDeviceImp
		:public CGLGraphicsDeviceImp
	{

	};

	class CGLES3GraphicsDeviceImp
		:public CGLES2GraphicsDeviceImp
	{

	};

	class CGLES3_1GraphicsDeviceImp
		:public CGLES3GraphicsDeviceImp
	{

	};

	class CGLES3_2GraphicsDeviceImp
		:public CGLES3_1GraphicsDeviceImp
	{

	};

	class CGL2GraphicsDeviceImp
		:public CGLGraphicsDeviceImp
	{

	};

	class CGL3GraphicsDeviceImp
		:public CGL2GraphicsDeviceImp
	{

	};

	class CGL3_1GraphicsDeviceImp
		:public CGL3GraphicsDeviceImp
	{

	};

	class CGL3_2GraphicsDeviceImp
		:public CGL3_1GraphicsDeviceImp
	{

	};

	class CGL3_3GraphicsDeviceImp
		:public CGL3_2GraphicsDeviceImp
	{

	};

	class CGL4GraphicsDeviceImp
		:public CGL3_3GraphicsDeviceImp
	{

	};

	class CGL4_1GraphicsDeviceImp
		:public CGL4GraphicsDeviceImp
	{

	};

	class CGL4_2GraphicsDeviceImp
		:public CGL4_1GraphicsDeviceImp
	{

	};

	class CGL4_3GraphicsDeviceImp
		:public CGL4_2GraphicsDeviceImp
	{

	};

	class CGL4_4GraphicsDeviceImp
		:public CGL4_3GraphicsDeviceImp
	{

	};

	class CGL4_5GraphicsDeviceImp
		:public CGL4_4GraphicsDeviceImp
	{

	};

	class CGL4_6GraphicsDeviceImp
		:public CGL4_5GraphicsDeviceImp
	{

	};
}