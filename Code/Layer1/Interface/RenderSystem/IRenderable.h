#pragma once
#include "IRenderGeometry.h"
#include "IRenderGeometryUsage.h"
#include "IRenderMaterial.h"
#include "IRenderSky.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderableObject;
		class IRenderable
		{
		protected:
			virtual ~IRenderable(){}
		public:
			virtual ISky * queryInterface_ISky()const=0;
			virtual const String & getName()const=0;
			virtual IRenderableObject * getObject()const=0;
			virtual IGeometryUsage * queryInterface_IGeometryUsage()const=0;
			virtual IMaterial * queryInterface_IMaterial()const=0;
			virtual Void setGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setVisible(Bool visible)=0;
			virtual Bool getVisible()const=0;
		};
	}
}