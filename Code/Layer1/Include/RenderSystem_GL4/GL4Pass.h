#pragma once
#include "GL4Enum.h"
#include "GL4Program.h"
#include "GL4Texture.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CTechnique;
			class CPass
			{
			protected:
				CEnum::EForwardPassType const mForwardType;
				CTechnique * const mTechnique;
				CProgram * mProgram;
				TVector<GLint> mEnabledState;
				TVector<GLint> mDisableState;
				TMap<VoidPtr,TVector<GLint>[2]> mStateFunctions;
				TVector<CTexture*> mVSTextures;
				TVector<CTexture*> mPSTextures;
			public:
				CPass();
				~CPass();
				CEnum::EForwardPassType getForwardType()const
				{
					return mForwardType;
				}
				CTechnique * getTechnique()const
				{
					return mTechnique;
				}
				decltype(mProgram) getProgram()const
				{
					return mProgram;
				}
				decltype(mVSTextures) const & getVSTextures()const
				{
					return mVSTextures;
				}
				decltype(mPSTextures) const & getPSTextures()const
				{
					return mPSTextures;
				}
				decltype(mEnabledState) const & getEnabledState()const
				{
					return mEnabledState;
				}
				decltype(mDisableState) const & getDisableState()const
				{
					return mDisableState;
				}
				decltype(mStateFunctions) const & getStateFunctions()const{ return mStateFunctions; }
			};
		}
	}
}