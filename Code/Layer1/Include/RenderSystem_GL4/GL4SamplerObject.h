#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			struct SSamplerDescription
				:public TBaseObject<SSamplerDescription>
			{
				TMap<GLenum,GLint> mStates;
				CFloatRGBA mBorderColor;
				Boolean operator==(const SSamplerDescription & test)const
				{
					return (mStates==test.mStates)&&(mBorderColor==test.mBorderColor);
				}
			};
			class CSamplerObject
				:public TBaseObject<CSamplerObject>
			{
			protected:
				GLuint mInternal;
				const SSamplerDescription mDesc;
			public:
				CSamplerObject(const SSamplerDescription & desc);
				~CSamplerObject();
				GLuint getInternal()const
				{
					return mInternal;
				}
				const SSamplerDescription & getDesc()const
				{
					return mDesc;
				}
			};
		}
	}
}