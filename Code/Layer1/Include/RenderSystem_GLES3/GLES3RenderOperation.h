#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class CPass;
			class CGeometry;
			class CConstantBuffer;
			class CRenderOperation
				:public TBaseObject<CRenderOperation>
			{
			public:
				CPass * mPass;
				GLint mVertexArrayObject;
				GLint mIndexBufferOffset;
				GLuint mIndexCount;
				GLint mVertexBufferOffset;
				GLuint mVertexCount;
				GLenum mPrimitiveTopology;
				TVector<CConstantBuffer*> mConstantBuffers;
				TVector<CUtility::SScissorRect> mScissorRects;
				CRenderOperation();
				~CRenderOperation();
				Void process();
			};
		}
	}
}