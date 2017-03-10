#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSResourceSystem;
ISystem * NSDevilX::NSResourceSystem::getSystem()
{
	return ISystemImp::getSingletonPtr();
}

NSDevilX::NSResourceSystem::ISystemImp::ISystemImp()
{}

NSDevilX::NSResourceSystem::ISystemImp::~ISystemImp()
{}