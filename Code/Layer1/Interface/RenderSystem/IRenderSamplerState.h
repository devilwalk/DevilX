#pragma once
#include "IRenderEnum.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISamplerState
		{
		protected:
			virtual ~ISamplerState(){}
		public:
			virtual Void setFilter(IEnum::ESamplerFilter filter)=0;
			virtual IEnum::ESamplerFilter getFilter()const=0;
			virtual Void setTextureAddressModeU(IEnum::ETextureAddressMode mode)=0;
			virtual IEnum::ETextureAddressMode getTextureAddressModeU()const=0;
			virtual Void setTextureAddressModeV(IEnum::ETextureAddressMode mode)=0;
			virtual IEnum::ETextureAddressMode getTextureAddressModeV()const=0;
			virtual Void setTextureAddressModeW(IEnum::ETextureAddressMode mode)=0;
			virtual IEnum::ETextureAddressMode getTextureAddressModeW()const=0;
			virtual Void setMipLODBias(Float bias)=0;
			virtual Float getMipLODBias()const=0;
			virtual Void setMaxAnisotropy(UInt32 value)=0;
			virtual UInt32 getMaxAnisotropy()const=0;
			virtual Void setComparisonFunction(IEnum::EComparisonFunction func)=0;
			virtual IEnum::EComparisonFunction getComparisonFunction()const=0;
			virtual Void setBorderColour(const CColour & colour)=0;
			virtual const CColour & getBorderColour()const=0;
			virtual Void setMinLOD(Float value)=0;
			virtual Float getMinLOD()const=0;
			virtual Void setMaxLOD(Float value)=0;
			virtual Float getMaxLOD()const=0;
		};
	}
}