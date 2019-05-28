#pragma once
#include "ICoreGACommandList.h"
namespace NSDevilX
{
	namespace NSCore
	{
		class IGACommandQueue_3D
		{
		protected:
			virtual ~IGACommandQueue_3D()
			{
			}
		public:
			virtual Void execute(IGACommandList_3D* commandList)=0;
			virtual Void execute(IGACommandList_Compute* commandList)=0;
			virtual Void execute(IGACommandList_Copy* commandList)=0;
		};
		class IGACommandQueue_Compute
		{
		protected:
			virtual ~IGACommandQueue_Compute()
			{
			}
		public:
			virtual Void execute(IGACommandList_Compute* commandList)=0;
			virtual Void execute(IGACommandList_Copy* commandList)=0;
		};
		class IGACommandQueue_Copy
		{
		protected:
			virtual ~IGACommandQueue_Copy()
			{
			}
		public:
			virtual Void execute(IGACommandList_Copy* commandList)=0;
		};
	}
}