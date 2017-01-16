#pragma once
#include "D3D11ConstantBuffer.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class CConstantBufferContainer
			{
			protected:
				const String mConstantBufferNameInShader;
				CConstantBuffer * mConstantBuffer;
				TSharedReadData<Bool> mNeedUpdate;
			public:
				CConstantBufferContainer(const String & constBufferNameInShader);
				virtual ~CConstantBufferContainer();
				CConstantBuffer * getConstantBufferMT();
				Void needUpdate()
				{
					mNeedUpdate.write(True);
				}
			protected:
				virtual Void _updateConstantBuffer(Byte * buffer)=0;
			};
		}
	}
}