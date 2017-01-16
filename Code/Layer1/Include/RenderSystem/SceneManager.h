#pragma once
#include "ISceneElementImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISceneImp;
		class CSceneManager
			:public TMessageReceiver<ISceneImp>
		{
		protected:
			ISceneImp * const mScene;
		public:
			CSceneManager(ISceneImp * scene);
			virtual ~CSceneManager();
			virtual IEnum::ESceneManagerAlgorithm getAlgorithm()const=0;
			virtual Void findVisibleObjects(const CPlaneBoundedVolume & bound,TVector<ISceneElementImp*> & visibleObjects)const=0;
			virtual Void findVisibleObjects(const DirectX::BoundingSphere & bound,TVector<ISceneElementImp*> & visibleObjects)const=0;
			// Inherited via TMessageReceiver
			virtual Void onMessage(ISceneImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		protected:
			virtual Void _addElement(IVisibleAreaImp * element)=0;
			virtual Void _removeElement(IVisibleAreaImp * element)=0;
		};
		class CSimpleSceneManager
			:public CSceneManager
			,public TBaseObject<CSimpleSceneManager>
		{
		protected:
			TSet<IVisibleAreaImp*> mElements;
		public:
			CSimpleSceneManager(ISceneImp * scene);
			~CSimpleSceneManager();

			// Inherited via CSceneManager
			virtual IEnum::ESceneManagerAlgorithm getAlgorithm() const override;
			virtual Void findVisibleObjects(const CPlaneBoundedVolume & bound,TVector<ISceneElementImp*> & visibleObjects) const override;
			virtual Void findVisibleObjects(const DirectX::BoundingSphere & bound,TVector<ISceneElementImp*> & visibleObjects) const override;
			virtual Void _addElement(IVisibleAreaImp * element) override;
			virtual Void _removeElement(IVisibleAreaImp * element) override;
		};
	}
}