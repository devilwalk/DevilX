#pragma once
#include "GLES3Geometry.h"
#include "GLES3OverlayMaterial.h"
#include "GLES3RenderOperation.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
		{
			class COverlayManager;
			class COverlayRenderable
				:public TBaseObject<COverlayRenderable>
				,public TMessageReceiver<IOverlayElementImp>
				,public TMessageReceiver<IColourUnitStateImp>
				,public TMessageReceiver<CVertexBufferImp>
				,public TMessageReceiver<CIndexBufferImp>
			{
			protected:
				COverlayMaterial * const mMaterial;
				const CFloat4 mScissorRectParameter;
				COverlayManager * const mManager;
				CGeometry * mGeometry;
				GLuint mVertexArrayObject;
				TVector<CFloat3> mPositions;
				TVector<CFloat2> mUVs;
				TVector<RGBA> mDiffuses;
				TVector<UInt32> mIndices;
				TList<UInt32> mFrees;
				TMap<IOverlayElementImp*,UInt32> mRectangles;
			public:
				COverlayRenderable(COverlayMaterial * material,const CFloat2 & scissorRectPosition,const CFloat2 & scissorRectSize,COverlayManager * manager);
				~COverlayRenderable();
				COverlayMaterial * getMaterial()const
				{
					return mMaterial;
				}
				const CFloat4 & getScissorRectParameter()const
				{
					return mScissorRectParameter;
				}
				const CFloat2 & getScissorRectPosition()const
				{
					return *reinterpret_cast<const CFloat2*>(&mScissorRectParameter);
				}
				const CFloat2 & getScissorRectSize()const
				{
					return *reinterpret_cast<const CFloat2*>(&mScissorRectParameter.z);
				}
				Boolean render(CRenderOperation & ro);
				Void addElement(IOverlayElementImp * element);
				Void removeElement(IOverlayElementImp * element);
				// Í¨¹ý TMessageReceiver ¼Ì³Ð
				virtual Void onMessage(IOverlayElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(IColourUnitStateImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CVertexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
				virtual Void onMessage(CIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			protected:
				Void _updateElementPosition(IOverlayElementImp * element);
				Void _updateElementTextureCoord(IOverlayElementImp * element);
				Void _updateElementDiffuse(IOverlayElementImp * element);
				Void _updateVertexArrayObject();
			};
		}
	}
}