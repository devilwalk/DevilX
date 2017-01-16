#pragma once
#include "CommonType.h"
#include "CommonMessageMode.h"
#include "CommonDefine.h"
namespace NSDevilX
{
	class CDirtyFlagContainer
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

	class CDirtyFlagContainerMT
	{
	protected:
		std::bitset<32> mDirtyFlag;
		CReadWriteLocker * mLocker[32];
	public:
		CDirtyFlagContainerMT()
		{
			for(int i=0;i<32;++i)
				mLocker[i]=new CReadWriteLocker;
		}
		virtual ~CDirtyFlagContainerMT()
		{
			for(auto locker:mLocker)
				delete locker;
		}
		Void addDirtyFlag(UInt32 flagIndex)
		{
			assert(flagIndex<32);
			mLocker[flagIndex]->lockWrite();
			if(!(mDirtyFlag[flagIndex]))
			{
				_preProcessDirtyFlagAdd(flagIndex);
				mDirtyFlag[flagIndex]=True;
				_postProcessDirtyFlagAdd(flagIndex);
			}
			mLocker[flagIndex]->unLockWrite();
		}
		Void removeDirtyFlag(UInt32 flagIndex)
		{
			assert(flagIndex<32);
			mLocker[flagIndex]->lockWrite();
			if(mDirtyFlag[flagIndex])
			{
				_preProcessDirtyFlagRemove(flagIndex);
				mDirtyFlag[flagIndex]=False;
				_postProcessDirtyFlagRemove(flagIndex);
			}
			mLocker[flagIndex]->unLockWrite();
		}
		Boolean hasDirtyFlag(UInt32 flagIndex)
		{
			Boolean ret=false;
			mLocker[flagIndex]->lockRead();
			ret=mDirtyFlag[flagIndex]?true:false;
			mLocker[flagIndex]->unLockRead();
			return ret;
		}
		Void process(UInt32 flag=-1)
		{
			Bool need_next_process=True;
			for(UInt32 i=0;i<32&&need_next_process;++i)
			{
				processSingle(i,&need_next_process);
			}
		}
		Void processSingle(UInt32 flagIndex,Bool * needProcessNext=nullptr)
		{
			Bool need_next_process=True;
			mLocker[flagIndex]->lockWrite();
			if(mDirtyFlag[flagIndex]&&_process(flagIndex,need_next_process))
			{
				mDirtyFlag[flagIndex]=false;
			}
			mLocker[flagIndex]->unLockWrite();
			if(needProcessNext)
				*needProcessNext=need_next_process;
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
	};
}