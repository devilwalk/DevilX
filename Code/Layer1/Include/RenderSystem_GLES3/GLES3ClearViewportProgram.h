#pragma once
#include "GLES3Program.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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