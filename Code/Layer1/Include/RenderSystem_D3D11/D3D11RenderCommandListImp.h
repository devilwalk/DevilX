#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CRenderCommandListImp
				:public CRenderCommandList
				,public TBaseObject<CRenderCommandListImp>
				,public CReferenceObject
			{
			protected:
				ID3D11DeviceContext * const mContext;
				ID3D11CommandList * mCommandList;
			public:
				CRenderCommandListImp(ID3D11DeviceContext * context);
				~CRenderCommandListImp();

				// Í¨¹ý CRenderCommandList ¼Ì³Ð
				virtual Void clearRenderTarget(CRenderTarget * renderTarget) override;
				virtual Void renderOperation(const CRenderOperation & op) override;
				virtual Void execute(Bool sync=False) override;
			};
		}
	}
}