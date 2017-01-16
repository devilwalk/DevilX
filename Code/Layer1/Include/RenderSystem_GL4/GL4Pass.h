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
				:public TBaseObject<CPass>
				,public TMessageReceiver<IMaterialImp>
				,public TMessageReceiver<IRenderableImp>
				,public TMessageReceiver<IGeometryImp>
				,public TMessageReceiver<ITextureUnitStateImp>
			{
			protected:
				CEnum::EForwardPassType const mForwardType;
				CTechnique * const mTechnique;
				CProgram * mProgram;
				GLuint mVertexArrayObject;
				TMap<VoidPtr,TVector<TVector<GLint> > > mStateFunctions;
				TVector<CTexture*> mVSTextures;
				TVector<CTexture*> mPSTextures;
			public:
				CPass(CTechnique * technique);
				CPass(CEnum::EForwardPassType type,CTechnique * technique);
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

				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(IMaterialImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IRenderableImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IGeometryImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(ITextureUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updateShader();
				Void _updateTextures();
				Void _updateRasterizerState();
				Void _updateBlendState();
				Void _updateDepthStencilState();
				Void _updateVertexArrayObject();
				Void _registerToIGeometryImp();
				Void _unregisterToIGeometryImp();
			};
		}
	}
}