#pragma once
#include "IRenderGeometry.h"
#include "IRenderGeometryUsage.h"
#include "IRenderMaterial.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderable
		{
		protected:
			virtual ~IRenderable(){ }
		public:
			virtual IGeometryUsage * queryInterface_IGeometryUsage()const=0;
			virtual Void setGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setVisible(Bool visible)=0;
			virtual Bool getVisible()const=0;
			virtual Void setMaterial(IMaterial * material)=0;
			virtual IMaterial * getMaterial()const=0;
		};
	}
}