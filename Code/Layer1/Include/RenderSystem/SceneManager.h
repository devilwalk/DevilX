#pragma once
#include "VisibleArea.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class CSceneManager
		{
		public:
			CSceneManager();
			virtual ~CSceneManager();
			virtual IEnum::ESceneManagerAlgorithm getAlgorithm()const=0;
			virtual Void addVisibleArea(CVisibleArea * area)=0;
			virtual Void removeVisibleAra(CVisibleArea * area)=0;
			virtual Void findVisibleObjects(const CPlaneBoundedVolume & bound,TVector(CVisibleArea*) & visibleObjects,UInt32 mask=-1)const=0;
			virtual Void findVisibleObjects(const DirectX::BoundingSphere & bound,TVector(CVisibleArea*) & visibleObjects,UInt32 mask=-1)const=0;
		};
		class CSimpleSceneManager
			:public CSceneManager
			,public TBaseObject<CSimpleSceneManager>
		{
		protected:
			TSet(CVisibleArea*) mElements;
		public:
			CSimpleSceneManager();
			~CSimpleSceneManager();

			// Inherited via CSceneManager
			virtual IEnum::ESceneManagerAlgorithm getAlgorithm() const override;
			virtual Void findVisibleObjects(const CPlaneBoundedVolume & bound,TVector(CVisibleArea*) & visibleObjects,UInt32 mask=-1) const override;
			virtual Void findVisibleObjects(const DirectX::BoundingSphere & bound,TVector(CVisibleArea*) & visibleObjects,UInt32 mask=-1) const override;
			virtual Void addVisibleArea(CVisibleArea * area) override;
			virtual Void removeVisibleAra(CVisibleArea * area) override;
		};
	}
}