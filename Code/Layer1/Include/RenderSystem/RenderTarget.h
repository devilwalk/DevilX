#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CRenderTarget
		{
		protected:
			TVector(Rect) mClearRects;
		public:
			CRenderTarget();
			virtual ~CRenderTarget();
			Void addClearRect(const Rect & rect)
			{
				mClearRects.push_back(rect);
			}
			const decltype(mClearRects) & getClearRects()const
			{
				return mClearRects;
			}
		};
		class CColourSurface
			:public CRenderTarget
		{
		protected:
			CFloatRGBA mClearColour;
		public:
			CColourSurface(){ }
			virtual ~CColourSurface(){ }
			Void setClearColour(const CColour & colour)
			{
				mClearColour=colour;
			}
			const decltype(mClearColour) & getClearColour()const
			{
				return mClearColour;
			}
			virtual Void initialize(UInt32 width,UInt32 height,IEnum::EColourSurfaceFormat format)=0;
		};
		class CDepthStencilSurface
			:public CRenderTarget
		{
		protected:
			Float mClearDepth;
			UInt8 mClearStencil;
			UInt8 mNeedClearDepth;
			UInt8 mNeedClearStencil;
		public:
			CDepthStencilSurface(){ }
			virtual ~CDepthStencilSurface(){ }
			Void setClearDepth(Bool clear,Float value)
			{
				mNeedClearDepth=static_cast<decltype(mNeedClearDepth)>(clear);
				mClearDepth=value;
			}
			Boolean isClearDepth()const
			{
				return mNeedClearDepth?true:false;
			}
			Float getClearDepth()const
			{
				return mClearDepth;
			}
			Void setClearStencil(Bool clear,UInt8 value)
			{
				mNeedClearStencil=static_cast<decltype(mNeedClearStencil)>(clear);
				mClearStencil=value;
			}
			Boolean isClearStencil()const
			{
				return mNeedClearStencil?true:false;
			}
			UInt8 getClearStencil()const
			{
				return mClearStencil;
			}
			virtual Void initialize(UInt32 width,UInt32 height,IEnum::EDepthStencilSurfaceFormat format)=0;
		};
	}
}