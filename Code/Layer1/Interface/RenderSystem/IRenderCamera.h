#pragma once
#include "IRenderEnum.h"
#include "IRenderSceneElement.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IPerspectiveProperty
		{
		protected:
			virtual ~IPerspectiveProperty(){ }
		public:
			virtual Void setFov(const CDegree & fov)=0;
			virtual const CDegree & getFov()const=0;
			virtual Void setAspectRatio(Float aspect)=0;
			virtual Float getAspectRatio()const=0;
		};
		class IOrthoProperty
		{
		protected:
			virtual ~IOrthoProperty()
			{
			}
		public:
			virtual Void setWidth(Float width)=0;
			virtual Float getWidth()const=0;
			virtual Void setHeight(Float height)=0;
			virtual Float getHeight()const=0;

		};
		class ICamera
		{
		protected:
			virtual ~ICamera(){ }
		public:
			virtual IPerspectiveProperty * queryInterface_IPerspectiveProperty()const=0;
			virtual IOrthoProperty * queryInterface_IOrthoProperty()const=0;
			virtual ISceneElement * queryInterface_ISceneElement()const=0;
			virtual Void setProjectionType(IEnum::EProjectionType type)=0;
			virtual IEnum::EProjectionType getProjectionType()const=0;
			virtual Void setNearClipPlane(Float nearClipPlane)=0;
			virtual Float getNearClipPlane()const=0;
			virtual Void setFarClipPlane(Float farClipPlane)=0;
			virtual Float getFarClipPlane()const=0;
			virtual Void setShadowReceiveDistance(Float distance)=0;
			virtual Float getShadowReceiveDistance()const=0;
			virtual Void setShadowReceiveFadeOutStartDistance(Float distance)=0;
			virtual Float getShadowReceiveFadeOutStartDistance()const=0;
			virtual Void addClipPlane(const CPlane & plane)=0;
			virtual UInt16 getClipPlaneCount()const=0;
			virtual Void setClipPlane(UInt16 index,const CPlane & plane)=0;
			virtual const CPlane & getClipPlane(UInt16 index)const=0;
			virtual Void removeAllClipPlane()=0;
		};
	}
}