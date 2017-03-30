#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CFontManager
			:public TBaseObject<CFontManager>
		{
		protected:
			NSResourceSystem::IResource * mFontResource;
		public:
			CFontManager();
			~CFontManager();
			NSResourceSystem::IResource * getFontResource()const
			{
				return mFontResource;
			}
		};
	}
}