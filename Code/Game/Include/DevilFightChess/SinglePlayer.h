#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CSinglePlayer
			:public TBaseObject<CSinglePlayer>
			,public CModule
		{
		protected:
		public:
			CSinglePlayer();
			~CSinglePlayer();
		};
	}
}