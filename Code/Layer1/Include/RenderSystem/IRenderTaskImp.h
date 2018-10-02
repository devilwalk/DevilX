#pragma once
#include "RenderTask.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IRenderTaskImp
			:public IRenderTask
		{
		protected:
			CRenderTask * mInternal;
		public:
			IRenderTaskImp();
			virtual ~IRenderTaskImp();
			CRenderTask * getInternal()const
			{
				return mInternal;
			}
			// Í¨¹ý IRenderTask ¼Ì³Ð
			virtual Void addChild(IRenderTask * task) override;
			virtual Void setSchemeName(const String & name) override;
		};
		class IClearTaskImp
			:public IClearTask
			,public IRenderTaskImp
		{
		protected:
		public:
			IClearTaskImp();
			~IClearTaskImp();
		};
	}
}