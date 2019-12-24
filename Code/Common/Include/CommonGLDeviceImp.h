#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLDeviceImp
			:public IDevice
		{
		protected:
		public:
			CGLDeviceImp();
			virtual ~CGLDeviceImp();

			virtual Bool createBufferPool(const TBufferPoolCreateInfos& createInfo,OUT IBufferPool* pool) override;
			virtual Bool createBuffer(const TBufferCreateInfos& createInfo,OUT IBuffer* buffer) override;
			virtual Bool createTexture(UINT width,UINT height,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture) override;
			virtual Bool createCubeTexture(UINT edageLength,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture) override;
			virtual Bool createVolumeTexture(UINT width,UINT height,UINT depth,UINT levels,DWORD usage,D3DFORMAT format,D3DPOOL pool,OUT ITexture* texture) override;
			virtual Bool createTexture1D(const D3D10_TEXTURE1D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture2D(const D3D10_TEXTURE2D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture3D(const D3D10_TEXTURE3D_DESC& desc,const D3D10_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture1D(const D3D11_TEXTURE1D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture2D(const D3D11_TEXTURE2D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture3D(const D3D11_TEXTURE3D_DESC& desc,const D3D11_SUBRESOURCE_DATA* initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLenum format,GLenum type,ConstVoidPtr initializeData,OUT ITexture* texture) override;
			virtual Bool createTexture2DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLboolean fixedsamplelocations,OUT ITexture* texture) override;
			virtual Bool createTexture3DMSAA(GLenum target,GLsizei samplers,GLenum internalformat,GLsizei width,GLsizei height,GLsizei depth,GLboolean fixedsamplelocations,OUT ITexture* texture) override;
			virtual Bool createCompressedTexture1D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture) override;
			virtual Bool createCompressedTexture2D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture) override;
			virtual Bool createCompressedTexture3D(GLenum target,GLint level,GLint internalformat,GLsizei width,GLsizei height,GLsizei depth,GLint border,GLsizei imageSize,ConstVoidPtr initializeData,OUT ITexture* texture) override;

			// 通过 IDevice 继承
			virtual Bool createVertexDeclaration(const D3DVERTEXELEMENT9* elements,OUT IInputLayout* layout) override;
			virtual Bool createInputLayout(const D3D10_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IInputLayout* layout) override;
			virtual Bool createInputLayout(const D3D11_INPUT_ELEMENT_DESC* descs,UINT numElements,ConstVoidPtr shaderBytecodeWithInputSignature,SIZE_T bytecodeLength,OUT IInputLayout* layout) override;
			virtual Bool vertexAttribFormat(GLuint attribindex,GLint size,GLenum type,GLboolean normalized,GLuint relativeoffset,OUT IInputLayout* layout) override;
			virtual Bool vertexAttribIFormat(GLuint attribindex,GLint size,GLenum type,GLuint relativeoffset,OUT IInputLayout* layout) override;
			virtual Bool vertexAttribPoint(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,ConstVoidPtr pointer,IBuffer* buffer,OUT IVertexArrayObject* layout) override;
			virtual Bool vertexAttribIPoint(GLuint index,GLint size,GLenum type,GLsizei stride,ConstVoidPtr pointer,IBuffer* buffer,OUT IVertexArrayObject* layout) override;

			// 通过 IDevice 继承
			virtual Bool createVertexShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader) override;
			virtual Bool createPixelShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader) override;
			virtual Bool createGeometryShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader) override;
			virtual Bool createHullShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader) override;
			virtual Bool createDomainShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader) override;
			virtual Bool createComputeShader(ConstVoidPtr bytecode,SizeT bytecodeSize,OUT IProgram* shader) override;
			virtual Bool createShader(GLenum type,ConstCharPtr string,GLint length,OUT IShader* shader) override;
			virtual Bool createShader(GLenum type,ConstCharPtr string,GLint length,OUT IProgram* shader) override;
			virtual Bool createShader(GLenum type,GLenum binaryFormat,ConstVoidPtr bytecode,GLsizei bytecodeSize,OUT IShader* shader) override;
			virtual Bool createShader(GLenum type,GLenum binaryFormat,ConstVoidPtr bytecode,GLsizei bytecodeSize,OUT IProgram* shader) override;
			virtual Bool attachProgram(GLenum type,IShader* shader,OUT IProgram* program) override;
			virtual Bool linkProgram(OUT IProgram* program) override;

			// 通过 IDevice 继承
			virtual Bool createBlendState(const D3D10_BLEND_DESC& desc,OUT IBlendState* state) override;
			virtual Bool createBlendState(const D3D10_BLEND_DESC1& desc,OUT IBlendState* state) override;
			virtual Bool createBlendState(const D3D11_BLEND_DESC& desc,OUT IBlendState* state) override;
			virtual Bool createBlendState(const D3D11_BLEND_DESC1& desc,OUT IBlendState* state) override;
			virtual Bool createDepthStencilState(const D3D10_DEPTH_STENCIL_DESC& desc,OUT IDepthStencilState* state) override;
			virtual Bool createDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& desc,OUT IDepthStencilState* state) override;
			virtual Bool createRasterizerState(const D3D10_RASTERIZER_DESC& desc,OUT IRasterizerState* state) override;
			virtual Bool createRasterizerState(const D3D11_RASTERIZER_DESC& desc,OUT IRasterizerState* state) override;
			virtual Bool createRasterizerState(const D3D11_RASTERIZER_DESC1& desc,OUT IRasterizerState* state) override;
			virtual Bool createRasterizerState(const D3D11_RASTERIZER_DESC2& desc,OUT IRasterizerState* state) override;

			// 通过 IDevice 继承
			virtual Bool createSamplerState(const D3D10_SAMPLER_DESC& desc,OUT ISamplerState* state) override;
			virtual Bool createSamplerState(const D3D11_SAMPLER_DESC& desc,OUT ISamplerState* state) override;
			virtual Bool getSurfaceLevel(ITexture* texture,UINT level,OUT ISurface* surface) override;
			virtual Bool getCubeMapSurface(ITexture* texture,D3DCUBEMAP_FACES faceType,UINT level,OUT ISurface* surface) override;
			virtual Bool createRenderTarget(UINT width,UINT height,D3DFORMAT format,D3DMULTISAMPLE_TYPE multiSample,DWORD multiSampleQuality,BOOL lockable,OUT ISurface* surface) override;
			virtual Bool createDepthStencilSurface(UINT width,UINT height,D3DFORMAT format,D3DMULTISAMPLE_TYPE multiSample,DWORD multiSampleQuality,BOOL discard,OUT ISurface* surface) override;
			virtual Bool renderbufferStorage(GLenum target,GLenum internalformat,GLsizei width,GLsizei height,OUT ISurface* surface) override;
			virtual Bool renderbufferStorageMultisample(GLenum target,GLsizei samples,GLenum internalformat,GLsizei width,GLsizei height,OUT ISurface* surface) override;
			virtual Bool createRenderTargetView(ITexture* resource,const D3D10_RENDER_TARGET_VIEW_DESC* desc,OUT IRenderTargetView* view) override;
			virtual Bool createRenderTargetView(ITexture* resource,const D3D11_RENDER_TARGET_VIEW_DESC* desc,OUT IRenderTargetView* view) override;
			virtual Bool createDepthStencilView(ITexture* resource,const D3D10_DEPTH_STENCIL_VIEW_DESC* desc,OUT IDepthStencilView* view) override;
			virtual Bool createDepthStencilView(ITexture* resource,const D3D11_DEPTH_STENCIL_VIEW_DESC* desc,OUT IDepthStencilView* view) override;
			virtual Bool framebufferTexture2D(GLenum target,GLenum attachment,GLenum textarget,ITexture* texture,GLint level,OUT IFrameBufferObject* fbo) override;
			virtual Bool framebufferTextureLayer(GLenum target,GLenum attachment,ITexture* texture,GLint level,GLint layer,OUT IFrameBufferObject* fbo) override;
			virtual Bool framebufferTexture(GLenum target,GLenum attachment,ITexture* texture,GLint level,OUT IFrameBufferObject* fbo) override;
			virtual Bool framebufferRenderbuffer(GLenum target,GLenum attachment,GLenum renderbuffertarget,ISurface* surface,OUT IFrameBufferObject* fbo) override;
			virtual Bool createShaderResourceView(IBuffer* resource,const D3D10_SHADER_RESOURCE_VIEW_DESC* desc,OUT IShaderResourceView* view) override;
			virtual Bool createShaderResourceView(ITexture* resource,const D3D10_SHADER_RESOURCE_VIEW_DESC* desc,OUT IShaderResourceView* view) override;
			virtual Bool createShaderResourceView(ITexture* resource,const D3D10_SHADER_RESOURCE_VIEW_DESC1* desc,OUT IShaderResourceView* view) override;
			virtual Bool createShaderResourceView(IBuffer* resource,const D3D11_SHADER_RESOURCE_VIEW_DESC* desc,OUT IShaderResourceView* view) override;
			virtual Bool createShaderResourceView(ITexture* resource,const D3D11_SHADER_RESOURCE_VIEW_DESC* desc,OUT IShaderResourceView* view) override;
		protected:
			virtual Bool _createBuffer(GLenum target,GLsizeiptr size,ConstVoidPtr initializeData,const TGLCompatible<GLenum>& usage,GLbitfield flags,OUT CGLBufferImp* buffer);
		};

		class CGLES2GraphicsDeviceImp
			:public CGLDeviceImp
		{
		public:
			CGLES2GraphicsDeviceImp();
			virtual ~CGLES2GraphicsDeviceImp();
		};

		class CGLES3GraphicsDeviceImp
			:public CGLES2GraphicsDeviceImp
		{
		public:
			CGLES3GraphicsDeviceImp();
			virtual ~CGLES3GraphicsDeviceImp();
		};

		class CGLES3_1GraphicsDeviceImp
			:public CGLES3GraphicsDeviceImp
		{
		public:
			CGLES3_1GraphicsDeviceImp();
			virtual ~CGLES3_1GraphicsDeviceImp();
		};

		class CGLES3_2GraphicsDeviceImp
			:public CGLES3_1GraphicsDeviceImp
		{
		public:
			CGLES3_2GraphicsDeviceImp();
			virtual ~CGLES3_2GraphicsDeviceImp();
		};

		class CGL2GraphicsDeviceImp
			:public CGLDeviceImp
		{
		public:
			CGL2GraphicsDeviceImp();
			virtual ~CGL2GraphicsDeviceImp();
		};

		class CGL3GraphicsDeviceImp
			:public CGL2GraphicsDeviceImp
		{
		public:
			CGL3GraphicsDeviceImp();
			virtual ~CGL3GraphicsDeviceImp();
		};

		class CGL3_1GraphicsDeviceImp
			:public CGL3GraphicsDeviceImp
		{
		public:
			CGL3_1GraphicsDeviceImp();
			virtual ~CGL3_1GraphicsDeviceImp();
		};

		class CGL3_2GraphicsDeviceImp
			:public CGL3_1GraphicsDeviceImp
		{
		public:
			CGL3_2GraphicsDeviceImp();
			virtual ~CGL3_2GraphicsDeviceImp();
		};

		class CGL3_3GraphicsDeviceImp
			:public CGL3_2GraphicsDeviceImp
		{
		public:
			CGL3_3GraphicsDeviceImp();
			virtual ~CGL3_3GraphicsDeviceImp();
		};

		class CGL4GraphicsDeviceImp
			:public CGL3_3GraphicsDeviceImp
		{
		public:
			CGL4GraphicsDeviceImp();
			virtual ~CGL4GraphicsDeviceImp();
		};

		class CGL4_1GraphicsDeviceImp
			:public CGL4GraphicsDeviceImp
		{
		public:
			CGL4_1GraphicsDeviceImp();
			virtual ~CGL4_1GraphicsDeviceImp();
		};

		class CGL4_2GraphicsDeviceImp
			:public CGL4_1GraphicsDeviceImp
		{
		public:
			CGL4_2GraphicsDeviceImp();
			virtual ~CGL4_2GraphicsDeviceImp();
		};

		class CGL4_3GraphicsDeviceImp
			:public CGL4_2GraphicsDeviceImp
		{
		public:
			CGL4_3GraphicsDeviceImp();
			virtual ~CGL4_3GraphicsDeviceImp();
		};

		class CGL4_4GraphicsDeviceImp
			:public CGL4_3GraphicsDeviceImp
		{
		public:
			CGL4_4GraphicsDeviceImp();
			virtual ~CGL4_4GraphicsDeviceImp();
		};

		class CGL4_5GraphicsDeviceImp
			:public CGL4_4GraphicsDeviceImp
		{
		public:
			CGL4_5GraphicsDeviceImp();
			virtual ~CGL4_5GraphicsDeviceImp();
		};

		class CGL4_6GraphicsDeviceImp
			:public CGL4_5GraphicsDeviceImp
		{
		public:
			CGL4_6GraphicsDeviceImp();
			virtual ~CGL4_6GraphicsDeviceImp();
		};
	}
}