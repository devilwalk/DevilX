#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CSamplerStateImp
				:public ISamplerStateImp
				,public TBaseObject<CSamplerStateImp>
			{
			protected:
				D3D11_SAMPLER_DESC mDescription;
				ID3D11SamplerState * mInternal;
			public:
				CSamplerStateImp();
				~CSamplerStateImp();

				virtual Void setFilter(IEnum::ESamplerFilter filter) override;
				virtual IEnum::ESamplerFilter getFilter() const override;
				virtual Void setTextureAddressModeU(IEnum::ETextureAddressMode mode) override;
				virtual IEnum::ETextureAddressMode getTextureAddressModeU() const override;
				virtual Void setTextureAddressModeV(IEnum::ETextureAddressMode mode) override;
				virtual IEnum::ETextureAddressMode getTextureAddressModeV() const override;
				virtual Void setTextureAddressModeW(IEnum::ETextureAddressMode mode) override;
				virtual IEnum::ETextureAddressMode getTextureAddressModeW() const override;
				virtual Void setMipLODBias(Float bias) override;
				virtual Float getMipLODBias() const override;
				virtual Void setMaxAnisotropy(UInt32 value) override;
				virtual UInt32 getMaxAnisotropy() const override;
				virtual Void setComparisonFunction(IEnum::EComparisonFunction func) override;
				virtual IEnum::EComparisonFunction getComparisonFunction()const override;
				virtual Void setBorderColour(const CColour & colour) override;
				virtual Void getBorderColour(OUT CColour & colour) const override;
				virtual Void setMinLOD(Float value) override;
				virtual Float getMinLOD() const override;
				virtual Void setMaxLOD(Float value) override;
				virtual Float getMaxLOD() const override;
			};
		}
	}
}