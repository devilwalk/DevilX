#pragma once
#include "CommonSTL.h"
namespace NSDevilX
{
	class CCommandQueue
	{
	public:
		class CCommand
		{
		public:
			enum EState
			{
				EState_Unstart,
				EState_Executing,
				EState_Finish
			};
		protected:
			EState mState;
		public:
			CCommand();
			virtual ~CCommand();
			virtual Boolean execute();
			virtual Boolean executing();
			virtual Boolean finish();
			virtual Boolean update();
		};
	protected:
		TList<CCommand*> mCommands;
	public:
		CCommandQueue();
		virtual ~CCommandQueue();
		virtual Void addCommand(CCommand * cmd,CCommand * flag=nullptr,Bool addAfter=True);
		virtual Void removeCommand(CCommand * cmd);
		virtual Void update();
	};
}