#pragma once
#include "IRenderSceneElement.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IQueryObject
		{
		protected:
			virtual ~IQueryObject(){}
		public:
			virtual ISceneElement * queryInterface_ISceneElement()const=0;
			virtual IGeometryUsage * queryInterface_IGeometryUsage()const=0;
			virtual Void setGeometry(IGeometry * geometry)=0;
			virtual IGeometry * getGeometry()const=0;
			virtual Void setVisible(Bool visible)=0;
			virtual Bool getVisible()const=0;
		};
	}
}