#pragma once
#include "CommonType.h"
#include "CommonMessageMode.h"
#include "CommonDefine.h"
namespace NSDevilX
{
	class CDirtyFlagContainer
		:public TMemoryAllocatorObject<CDirtyFlagContainer>
	{
	protected:
		UInt32 mDirtyFlag;
	public:
		CDirtyFlagContainer()
			:mDirtyFlag(0)
		{}
		virtual ~CDirtyFlagContainer()
		{}
		Void addDirtyFlag(UInt32 flagIndex)
		{
			UInt32 flag=1<<flagIndex;
			if(!(getDirtyFlag()&flag))
			{
				_preProcessDirtyFlagAdd(flagIndex);
				mDirtyFlag|=flag;
				_postProcessDirtyFlagAdd(flagIndex);
			}
		}
		Void removeDirtyFlag(UInt32 flagIndex)
		{
			UInt32 flag=1<<flagIndex;
			if(getDirtyFlag()&flag)
			{
				_preProcessDirtyFlagRemove(flagIndex);
				mDirtyFlag&=~flag;
				_postProcessDirtyFlagRemove(flagIndex);
			}
		}
		UInt32 getDirtyFlag()const
		{
			return mDirtyFlag;
		}
		Boolean hasDirtyFlag(UInt32 flagIndex)const
		{
			UInt32 flag=1<<flagIndex;
			return 0!=(getDirtyFlag()&flag);
		}
		Void process(UInt32 flag=-1)
		{
			_preProcess(flag);
			Bool need_next_process=True;
			for(UInt32 i=0;need_next_process&&getDirtyFlag()&&(i<32);++i)
			{
				if((1<<i)&flag)
					processSingle(i,&need_next_process);
			}
			_postProcess(flag);
		}
		Void processSingle(UInt32 flagIndex,Bool * needProcessNext=nullptr)
		{
			UInt32 flag=1<<flagIndex;
			if(getDirtyFlag()&flag)
			{
				_preProcessSingle(flagIndex);
				Bool need_next_process=True;
				if(_process(flagIndex,need_next_process))
				{
					removeDirtyFlag(flagIndex);
				}
				if(needProcessNext)
					*needProcessNext=need_next_process;
				_postProcessSingle(flagIndex);
			}
		}
	protected:
		virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess)
		{
			return false;
		}
		virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex)
		{}
		virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex)
		{}
		virtual Void _preProcessDirtyFlagRemove(UInt32 flagIndex)
		{}
		virtual Void _postProcessDirtyFlagRemove(UInt32 flagIndex)
		{}
		virtual Void _preProcess(UInt32 flag)
		{}
		virtual Void _postProcess(UInt32 flag)
		{}
		virtual Void _preProcessSingle(UInt32 flagIndex)
		{}
		virtual Void _postProcessSingle(UInt32 flagIndex)
		{}
	};
}