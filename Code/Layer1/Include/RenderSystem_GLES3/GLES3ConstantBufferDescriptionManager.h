#pragma once
#include "GLES3ConstantBufferDescription.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		namespace NSGLES3
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