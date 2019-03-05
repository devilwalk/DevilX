#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSCore;
using namespace NSDX11;

NSDevilX::NSCore::NSDX11::IGABufferImp::IGABufferImp(ID3D11Device * device,const IGPUStruct::SBufferDesc & desc,const IGPUStruct::SSubResourceData * initialData)
	:mInternal(nullptr)
{
	if(initialData)
		device->CreateBuffer(&CMapper::mapping(desc),&CMapper::mapping(*initialData),&mInternal);
	else
		device->CreateBuffer(&CMapper::mapping(desc),NULL,&mInternal);
}

NSDevilX::NSCore::NSDX11::IGABufferImp::~IGABufferImp()
{
	DEVILX_COM_SAFE_RELEASE(mInternal);
}
