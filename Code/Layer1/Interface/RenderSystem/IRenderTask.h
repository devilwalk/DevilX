#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITask
		{
		protected:
			virtual ~ITask(){ }
		public:
			virtual Void addChild(ITask * task)=0;
		};
		class IRenderableTask
		{
		protected:
			virtual ~IRenderableTask()
			{
			}
		public:
			virtual ITask * queryInterface_ITask()const=0;
			virtual Void setViewport(IViewport * vp)=0;
			virtual Void addRenderable(IRenderable * renderable)=0;
			virtual Void setSchemeName(const String & name)=0;
		};
		class IRenderSceneTask
		{
		protected:
			virtual ~IRenderSceneTask()
			{
			}
		public:
			virtual ITask * queryInterface_ITask()const=0;
			virtual Void setViewport(IViewport * vp)=0;
			virtual Void setSchemeName(const String & name)=0;
		};
		class IClearRenderTargetTask
		{
		protected:
			virtual ~IClearRenderTargetTask()
			{
			}
		public:
			virtual ITask * queryInterface_ITask()const=0;
			virtual Void addRenderTarget(IRenderTarget * renderTarget)=0;
		};
		class IRenderQuadTask
		{
		protected:
			virtual ~IRenderQuadTask()
			{
			}
		public:
			virtual ITask * queryInterface_ITask()const=0;
			virtual Void setViewport(IViewport * vp)=0;
			virtual Void setMaterial(IMaterial * material)=0;
			virtual Void setSchemeName(const String & name)=0;
		};
	}
}