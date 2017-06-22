#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CConstantBufferDescription
				:public TBaseObject<CConstantBufferDescription>
			{
			public:
				struct SConstant
				{
					String mName;
					UInt32 mOffsetInBytes;
					GLenum mType;
				};
			protected:
				String mName;
				UInt32 mSizeInBytes;
				TMap<const String,const SConstant> mConstantDescriptions;
			public:
				CConstantBufferDescription(GLuint program,GLuint index);
				~CConstantBufferDescription();
				const String & getName()const
				{
					return mName;
				}
				decltype(mSizeInBytes) getSizeInBytes()const
				{
					return mSizeInBytes;
				}
				const SConstant & getConstantDesc(const String & name)const
				{
					return mConstantDescriptions.get(name);
				}
				const decltype(mConstantDescriptions) & getConstantDescriptions()const
				{
					return mConstantDescriptions;
				}
			};
		}
	}
}