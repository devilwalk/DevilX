#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CResource
		{
		protected:
		public:
			CResource(){ }
			virtual ~CResource(){ }
		};
		class CBuffer
			:public CResource
		{
		protected:
			IEnum::EBufferType mType;
			UInt32 mSize;
		public:
			CBuffer():mType(IEnum::EBufferType_VertexBuffer),mSize(0){ }
			virtual ~CBuffer(){ }
			IEnum::EBufferType getType()const
			{
				return mType;
			}
			UInt32 getSize()const
			{
				return mSize;
			}
			virtual Void initialize(IEnum::EBufferType type,UInt32 sizeInBytes,UInt32 flag=IEnum::EBufferFlag_GPURead,ConstVoidPtr data=nullptr)
			{
				mType=type;
				mSize=sizeInBytes;
			}
			virtual Void updateData(ConstVoidPtr data,UInt32 offsetInBytes=0,UInt32 sizeInBytes=0)=0;
			virtual Void bind(UInt32 offsetInBytes,IEnum::EAutoPropgramParameterDataSource source)=0;
			virtual Void unbind(UInt32 offsetInBytes)=0;
		};
		class CTexture
			:public CResource
		{
		protected:
			IEnum::ETextureType mType;
		public:
			CTexture():mType(IEnum::ETextureType_2D){ }
			virtual ~CTexture(){ }
			virtual Void initialize(IEnum::ETextureType type,UInt32 width,UInt32 height)
		};
		class CShader
			:public CResource
		{
		protected:
			IEnum::EShaderType mType;
			IEnum::EShaderCodeType mCodeType;
		public:
			CShader()
				:mType(IEnum::EShaderType_VS)
				,mCodeType(IEnum::EShaderCodeType_HLSL_5_0)
			{
			}
			virtual ~CShader()
			{
			}
			IEnum::EShaderType getType()const
			{
				return mType;
			}
			IEnum::EShaderCodeType getCodeType()const
			{
				return mCodeType;
			}
			virtual Boolean compile(IEnum::EShaderType type,IEnum::EShaderCodeType codeType,const String & code)
			{
				mType=type;
				mCodeType=codeType;
			}
		};
		class CProgram
			:public CResource
		{
		protected:
			std::array<CShader*,5> mShaders;
		public:
			CProgram()
			{
				memset(&mShaders[0],0,5*sizeof(CShader*));
			}
			virtual ~CProgram()
			{
			}
			CShader * getShader(IEnum::EShaderType type)const
			{
				return mShaders[type];
			}
			virtual Void setShader(IEnum::EShaderType type,CShader * shader)
			{
				mShaders[type]=shader;
			}
			virtual IEnum::EProgramResourceType getResourceType(const String & name)const=0;
			virtual UInt32 getResourceLocation(const String & name)const=0;
			virtual IProgramBufferLayout * getBufferLayout(UInt32 resourceLocation)const=0;
		};
	}
}