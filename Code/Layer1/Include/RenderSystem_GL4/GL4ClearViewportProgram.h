#pragma once
#include "GL4Program.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CClearViewportProgram
				:public TBaseObject<CClearViewportProgram>
			{
			protected:
				CProgram * mProgram;
			public:
				CClearViewportProgram();
				~CClearViewportProgram();
				CProgram * getProgram()const
				{
					return mProgram;
				}
			};
		}
	}
}