#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CPass;
			class CGeometryImp;
			class CConstantBuffer;
			class CRenderOperation
				:public TBaseObject<CRenderOperation>
			{
			public:
				ID3D11DeviceContext1 * const mContext;
				TVector<ID3D11Buffer*> mVertexBuffers;
				TVector<UInt32> mVertexStrides;
				ID3D11Buffer * mIndexBuffer;
				CPass * mPass;
				UINT mIndexBufferOffset;
				UINT mIndexCount;
				UINT mVertexBufferOffset;
				UINT mVertexCount;
				D3D11_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
				TVector<CConstantBuffer*> mConstantBuffers;
				TVector<D3D11_RECT> mScissorRects;
				CRenderOperation(ID3D11DeviceContext1 * context);
				~CRenderOperation();
				Void process();
			};
		}
	}
}