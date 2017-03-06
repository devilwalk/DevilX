#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CEntity::CEntity(CScene * scene)
	:mScene(scene)
	,mHP(0)
	,mMP(0)
	,mAttack(0)
	,mDefense(0)
	,mSpeed(0)
	,mGrid(nullptr)
{}

NSDevilX::NSFightChess::CEntity::~CEntity()
{}