#pragma once
#include "D3D11ConstantBufferDescription.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CConstantBufferDescriptionManager
				:public TBaseObject<CConstantBufferDescriptionManager>
			{
			protected:
				TNamedResourcePtrContainer<CConstantBufferDescription> mDescriptions;
			public:
				CConstantBufferDescriptionManager();
				~CConstantBufferDescriptionManager();
				Void registerDescription(ID3D11ShaderReflectionConstantBuffer * reflection);
				CConstantBufferDescription * getDescription(const String & constBufferName)const;
			};
		}
	}
}