#pragma once
#include "GLES3Enum.h"
#include "GLES3Pass.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CEntityTechnique;
			class CEntityPass
				:public TBaseObject<CEntityPass>
				,public CPass
				,public TMessageReceiver<ISubEntityImp>
				,public TMessageReceiver<IGeometryImp>
				,public TMessageReceiver<ITextureUnitStateImp>
			{
			protected:
				CEnum::EForwardPassType const mForwardType;
				CEntityTechnique * const mTechnique;
				GLuint mVertexArrayObject;
			public:
				CEntityPass(CEntityTechnique * technique);
				CEntityPass(CEnum::EForwardPassType type,CEntityTechnique * technique);
				~CEntityPass();
				CEnum::EForwardPassType getForwardType()const
				{
					return mForwardType;
				}
				CEntityTechnique * getTechnique()const
				{
					return mTechnique;
				}
				GLuint getVertexArrayObject()const
				{
					return mVertexArrayObject;
				}
				// ͨ�� TMessageReceiver �̳�
				virtual Void onMessage(ISubEntityImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
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