#pragma once
#include "InputConfig.h"
namespace NSDevilX
{
	namespace NSDevilCraft
	{
		class CActor
		{
		protected:
			TList<UInt32> mActions;
			CInputConfig * mInputConfig;
		public:
			CActor();
			virtual ~CActor();
			Void setInputConfig(CInputConfig * config)
			{
				mInputConfig=config;
			}
			virtual Void addAction(UInt32 action);
		};
	}
}