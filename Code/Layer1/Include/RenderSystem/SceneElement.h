#pragma once
#include "Renderable.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CVisibleArea;
		class CSceneElement
			:public CReferenceObject
		{
		protected:
			CVisibleArea * mVisibleArea;
			UInt32 mVisibleMask;
			TVector(CRenderable*) mRenderables;
		public:
			CSceneElement();
			virtual ~CSceneElement();
			Void setVisibleArea(CVisibleArea * area)
			{
				mVisibleArea=area;
			}
			CVisibleArea * getVisibleArea()const
			{
				return mVisibleArea;
			}
			Void setVisibleMask(UInt32 mask)
			{
				mVisibleMask=mask;
			}
			UInt32 getVisibleMask()const
			{
				return mVisibleMask;
			}
			decltype(mRenderables) const & getRenderables()const
			{
				return mRenderables;
			}
		};
	}
}