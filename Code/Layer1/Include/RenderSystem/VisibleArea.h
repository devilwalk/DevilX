#pragma once
#include "SceneElement.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CScene;
		class CVisibleArea
			:public TBaseObject<CVisibleArea>
		{
		protected:
			CScene * const mScene;
			Bool mEnable;
			UInt32 mMask;
			DirectX::BoundingBox mAABB;
			TSet(CSceneElement*) mElements;
		public:
			CVisibleArea(CScene * scene);
			~CVisibleArea();
			Void setEnable(Bool enable)
			{
				mEnable=enable;
			}
			Bool getEnable()const
			{
				return mEnable;
			}
			UInt32 getMask()const
			{
				return mMask;
			}
			Boolean hasMask(UInt32 mask)const
			{
				return 0!=(mMask&mask);
			}
			Void setBoundingBox(const DirectX::BoundingBox & aabb)
			{
				mAABB=aabb;
			}
			const DirectX::BoundingBox & getBoundingBox()const
			{
				return mAABB;
			}
			Void attach(CSceneElement * element)
			{
				element->setVisibleArea(this);
				mElements.insert(element);
				_addMask(element->getVisibleMask());
			}
			Void detach(CSceneElement * element)
			{
				element->setVisibleArea(nullptr);
				mElements.erase(element);
				_updateMask();
			}
			decltype(mElements) const & getAttachedObjects()const
			{
				return mElements;
			}
		protected:
			Void _addMask(UInt32 mask)
			{
				mMask|=mask;
			}
			Void _updateMask()
			{
				mMask=0;
				for(auto element:mElements)
					_addMask(element->getVisibleMask());
			}
		};
	}
}