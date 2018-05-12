#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::CCommandQueue::CCommand::CCommand()
	:mState(EState_Initialize)
{
}

NSDevilX::CCommandQueue::CCommand::~CCommand()
{
}

Boolean NSDevilX::CCommandQueue::CCommand::start()
{
	return true;
}

Boolean NSDevilX::CCommandQueue::CCommand::execute()
{
	return true;
}

Boolean NSDevilX::CCommandQueue::CCommand::finish()
{
	return true;
}

Boolean NSDevilX::CCommandQueue::CCommand::update()
{
	switch(mState)
	{
	case EState_Initialize:
		if(start())
			mState=EState_Executing;
		return true;
	case EState_Executing:
		if(execute())
			mState=EState_Finish;
		return true;
	case EState_Finish:
		if(finish())
			return false;
		else
			return true;
	default:
		return false;
	}
}

NSDevilX::CCommandQueue::CCommandQueue()
{
}

NSDevilX::CCommandQueue::~CCommandQueue()
{
}

Void NSDevilX::CCommandQueue::addCommand(CCommand * cmd,CCommand * flag,Bool addAfter)
{
	auto add_pos=mCommands.cend();
	if(flag)
	{
		add_pos=mCommands.find(flag);
		assert(add_pos!=mCommands.cend());
		if(addAfter)
		{
			++add_pos;
		}
	}
	mCommands.insert(add_pos,cmd);
}

Void NSDevilX::CCommandQueue::removeCommand(CCommand * cmd)
{
	mCommands.remove(cmd);
}

Void NSDevilX::CCommandQueue::update()
{
	if((!mCommands.empty())&&(!mCommands.front()->update()))
		mCommands.pop_front();
}
