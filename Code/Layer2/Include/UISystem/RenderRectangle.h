#pragma once
namespace NSDevilX
{
	namespace NSUISystem
	{
		class CRenderRectangle
			:public TBaseObject<CRenderRectangle>
		{
			friend class CRenderManager;
		protected:
			const UInt32 mVertexIndex;
		public:
			Void setPosition(const CFloat3 & lt,const CFloat3 & rt,const CFloat3 & lb,const CFloat3 & rb);
			Void setTextureCoord(const CFloat2 & lt,const CFloat2 & rt,const CFloat2 & lb,const CFloat2 & rb);
			Void setDiffuse(const CColour & lt,const CColour & rt,const CColour & lb,const CColour & rb);
		protected:
			CRenderRectangle(UInt32 vertexIndex);
			~CRenderRectangle();
		};
	}
}