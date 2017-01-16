#pragma once
#include "IRenderTransformer.h"
#include "IRenderSceneElement.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IScene;
		class IVisibleArea
		{
		protected:
			virtual ~IVisibleArea(){}
		public:
			virtual const String & getName()const=0;
			virtual IScene * getScene()const=0;
			virtual Void setVisible(Bool visible)=0;
			virtual Bool getVisible()const=0;
			virtual Void setTransformer(ITransformer * transformer)=0;
			virtual ITransformer * getTransformer()const=0;
			virtual Void setBoundingBox(const DirectX::BoundingBox & aabb)=0;
			virtual const DirectX::BoundingBox & getBoundingBox()const=0;
			virtual Void attachObject(ISceneElement * element)=0;
			virtual Void detachObject(ISceneElement * element)=0;
		};
	}
}