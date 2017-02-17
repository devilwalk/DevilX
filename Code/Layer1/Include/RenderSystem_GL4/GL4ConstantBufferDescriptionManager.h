#pragma once
#include "GL4ConstantBufferDescription.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGL4
		{
			class CConstantBufferDescriptionManager
				:public TBaseObject<CConstantBufferDescriptionManager>
			{
			protected:
				TNamedResourcePtrMap<CConstantBufferDescription> mDescriptions;
			public:
				CConstantBufferDescriptionManager();
				~CConstantBufferDescriptionManager();
				Void registerDescription(GLuint program,GLuint index);
				CConstantBufferDescription * getDescription(const String & constBufferName)const;
			};
		}
	}
}