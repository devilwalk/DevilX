#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CVertexBuffer
				:public TBaseObject<CVertexBuffer>
				,public CGLResourceObject
			{
			protected:
				const CEnum::EVertexBufferType mType;
			public:
				CVertexBuffer(CEnum::EVertexBufferType type);
				~CVertexBuffer();
				CEnum::EVertexBufferType getType()const
				{
					return mType;
				}
			};
		}
	}
}