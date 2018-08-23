#pragma once
namespace NSDevilX
{
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