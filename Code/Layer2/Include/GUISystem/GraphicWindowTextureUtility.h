#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class CGraphicWindowTextureUtility
			:public TBaseObject<CGraphicWindowTextureUtility>
		{
		protected:
			NSUISystem::IGraphicWindow * const mGraphicWindow;
			NSResourceSystem::IResource * mTextureResource;
		public:
			CGraphicWindowTextureUtility(NSUISystem::IGraphicWindow * graphicWindow);
			~CGraphicWindowTextureUtility();
			Void setTexture(NSResourceSystem::IResource * resource,const CUInt2 & pixelStart=CUInt2::sZero,const CUInt2 & pixelEnd=CUInt2::sOne);
			NSResourceSystem::IResource * getTextureResource()const
			{
				return mTextureResource;
			}
		};
	}
}