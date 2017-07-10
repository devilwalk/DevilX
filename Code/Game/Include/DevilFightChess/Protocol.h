#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CProtocol
		{
		protected:
		public:
			CProtocol()
			{}
			virtual ~CProtocol()
			{}
		};
		class CProtocol_PlayAddinRequest
			:public CProtocol
			,public TBaseObject<CProtocol_PlayAddinRequest>
		{
		protected:
		public:
			CProtocol_PlayAddinRequest();
			~CProtocol_PlayAddinRequest();
		};
	}
}