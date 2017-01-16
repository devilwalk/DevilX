#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CPass;
			class CGeometry;
			class CConstantBuffer;
			class CRenderOperation
				:public TBaseObject<CRenderOperation>
			{
			public:
				ID3D11DeviceContext1 * const mContext;
				CGeometry * mGeometry;
				CPass * mPass;
				UINT mIndexBufferOffset;
				UINT mIndexCount;
				UINT mVertexBufferOffset;
				UINT mVertexCount;
				D3D11_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
				TVector<CConstantBuffer*> mConstantBuffers;
				CRenderOperation(ID3D11DeviceContext1 * context);
				~CRenderOperation();
				Void process();
			};
		}
	}
}