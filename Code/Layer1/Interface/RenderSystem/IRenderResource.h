#pragma once
#include "IRenderGeometry.h"
#include "IRenderTexture.h"
#include "IRenderBuffer.h"
#include "IRenderProgram.h"
#include "IRenderShader.h"
#include "IRenderMaterial.h"
#include "IRenderSamplerState.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IResource
		{
		protected:
			virtual ~IResource(){ }
		public:
			virtual const String & getName()const=0;
			virtual IGeoemtry * queryInterface_IGeometry()const=0;
			virtual ITexture1D * queryInterface_ITexture1D()const=0;
			virtual ITexture2D * queryInterface_ITexture2D()const=0;
			virtual ITexture3D * queryInterface_ITexture3D()const=0;
			virtual IBuffer * queryInterface_IBuffer()const=0;
			virtual IProgram * queryInterface_IProgram()const=0;
			virtual IShader * queryInterface_IShadre()const=0;
			virtual IMaterial * queryInterface_IMaterial()const=0;
			virtual ISamplerState * queryInterface_ISamplerState()const=0;
		};
	}
}