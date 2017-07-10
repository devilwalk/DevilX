#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CMatchTeam
			:public TBaseObject<CMatchTeam>
		{
		protected:
			const String mName;
		public:
			CMatchTeam(const String & name);
			~CMatchTeam();
		};
	}
}