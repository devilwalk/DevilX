#pragma once
#include "IGameObject.h"
namespace NSDevilX
{
	namespace NSGameEngine
	{
		class ISceneNode
		{
		protected:
			virtual ~ISceneNode(){ }
		public:
			virtual const String & getName()const=0;
			virtual Void attach(IObject * obj)=0;
			virtual Void dettach(IObject * obj)=0;
		};
	}
}