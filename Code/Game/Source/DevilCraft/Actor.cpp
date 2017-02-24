#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSDevilCraft;

NSDevilX::NSDevilCraft::CActor::CActor()
{}

NSDevilX::NSDevilCraft::CActor::~CActor()
{}

Void NSDevilX::NSDevilCraft::CActor::addAction(UInt32 action)
{
	mActions.push_back(action);
}
