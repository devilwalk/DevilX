#pragma once
#include "D3D11Geometry.h"
#include "D3D11OverlayMaterial.h"
#include "D3D11RenderOperation.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSD3D11
		{
			class COverlayManager;
			class COverlayRenderable
				:public TBaseObject<COverlayRenderable>
				,public TMessageReceiver<IOverlayElementImp>
				,public TMessageReceiver<IColourUnitStateImp>
			{
			protected:
				COverlayMaterial * const mMaterial;
				COverlayManager * const mManager;
				CGeometry * mGeometry;
				TVector<CFloat3> mPositions;
				TVector<CFloat2> mUVs;
				TVector<RGBA> mDiffuses;
				TVector<UInt32> mIndices;
				TList<UInt32> mFrees;
				TMap<IOverlayElementImp*,UInt32> mRectangles;
			public:
				COverlayRenderable(COverlayMaterial * material,COverlayManager * manager);
				~COverlayRenderable();
				COverlayMaterial * getMaterial()const
				{
					return mMaterial;
				}
				Void render(CRenderOperation & ro);
				Void addElement(IOverlayElementImp * element);
				Void removeElement(IOverlayElementImp * element);
				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(IOverlayElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updateElementPosition(IOverlayElementImp * element);
				Void _updateElementTextureCoord(IOverlayElementImp * element);
				Void _updateElementDiffuse(IOverlayElementImp * element);
			};
		}
	}
}