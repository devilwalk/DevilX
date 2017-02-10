#pragma once
#include "IGraphicWindowImp.h"
namespace NSDevilX
{
	namespace NSUISystem
	{
		class CRenderable
			:public TBaseObject<CRenderable>
			,public TMessageReceiver<IGraphicWindowImp>
		{
		public:
			struct SRenderGeometry
				:public TBaseObject<SRenderGeometry>
			{
				TVector<CFloat3> mPositions;
				TVector<CFloat2> mTextureCoords;
				TVector<RGBA> mDiffuses;
				TList<UInt32> mFreeIndexList;
				NSRenderSystem::IGeometry * mGeometry;
				SRenderGeometry();
				~SRenderGeometry();
				UInt32 allocRectangle();
				Void freeRectangle(UInt32 vertexIndex);
			};
		protected:
			const CImage * const mImage;
			SRenderGeometry * mGeometry;
		public:
			CRenderable(const CImage * img);
			~CRenderable();
			const CImage * getImage()const
			{
				return mImage;
			}
			Void addImageWindow(IGraphicWindowImp * window);
			Void removeImageWindow(IGraphicWindowImp * window);
		};
	}
}