#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CPass;
			class CGeometry;
			class CConstantBuffer;
			class CRenderOperation
				:public TBaseObject<CRenderOperation>
			{
			public:
				CGeometry * mGeometry;
				CPass * mPass;
				GLint mIndexBufferOffset;
				GLuint mIndexCount;
				GLint mVertexBufferOffset;
				GLuint mVertexCount;
				GLenum mPrimitiveTopology;
				TVector<CConstantBuffer*> mConstantBuffers;
				CRenderOperation();
				~CRenderOperation();
				Void process();
			};
		}
	}
}