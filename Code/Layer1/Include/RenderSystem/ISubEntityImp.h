#pragma once
#include "IRenderableImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IEntityImp;
		class ISubEntityImp
			:public ISubEntity
			,public CUserDataContainer
			,public CReferenceObject
		{
		public:
		protected:
			const String mName;
			IEntityImp * const mObject;
			IRenderableImp * mRenderable;
		public:
			ISubEntityImp(const String & name,IEntityImp * object);
			// Inherited via IRenderable
			virtual IRenderable * queryInterface_IRenderable() const override;
			virtual const String & getName() const override;
			virtual IEntity * getEntity() const override;
		protected:
			~ISubEntityImp();
		};
	}
}