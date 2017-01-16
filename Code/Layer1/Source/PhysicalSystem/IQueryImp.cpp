#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSPhysicalSystem;

NSDevilX::NSPhysicalSystem::IQueryImp::IQueryImp(const String & name,ISceneImp * scene)
	:mName(name)
	,mScene(scene)
	,mResultMask(0)
	,mResultReceiver(nullptr)
{}

NSDevilX::NSPhysicalSystem::IQueryImp::~IQueryImp()
{}

IRayQuery * NSDevilX::NSPhysicalSystem::IQueryImp::queryInterface_IRayQuery() const
{
	return nullptr;
}

const String & NSDevilX::NSPhysicalSystem::IQueryImp::getName() const
{
	// TODO: insert return statement here
	return mName;
}

Void NSDevilX::NSPhysicalSystem::IQueryImp::addResultType(IEnum::EQueryResultType type)
{
	UInt32 mask=1<<type;
	mResultMask|=mask;
}

Void NSDevilX::NSPhysicalSystem::IQueryImp::removeResultType(IEnum::EQueryResultType type)
{
	UInt32 mask=1<<type;
	mResultMask&=~mask;
}

Boolean NSDevilX::NSPhysicalSystem::IQueryImp::hasResultType(IEnum::EQueryResultType type) const
{
	UInt32 mask=1<<type;
	return 0!=(mask&mResultMask);
}

Void NSDevilX::NSPhysicalSystem::IQueryImp::setResultReceiver(IQueryResultReceiver * receiver)
{
	mResultReceiver=receiver;
}

IQueryResultReceiver * NSDevilX::NSPhysicalSystem::IQueryImp::getResultReceiver() const
{
	return mResultReceiver;
}

Void NSDevilX::NSPhysicalSystem::IQueryImp::execute()
{
	notify(EMessage_Execute);
}

NSDevilX::NSPhysicalSystem::IRayQueryImp::IRayQueryImp(const String & name,ISceneImp * scene)
	:IQueryImp(name,scene)
{}

NSDevilX::NSPhysicalSystem::IRayQueryImp::~IRayQueryImp()
{}

IRayQuery * NSDevilX::NSPhysicalSystem::IRayQueryImp::queryInterface_IRayQuery() const
{
	return const_cast<IRayQueryImp*>(this);
}

IEnum::EQueryType NSDevilX::NSPhysicalSystem::IRayQueryImp::getType() const
{
	return IEnum::EQueryType_Ray;
}

Void NSDevilX::NSPhysicalSystem::IRayQueryImp::setRay(const CRay & ray)
{
	mRay=ray;
}

const CRay & NSDevilX::NSPhysicalSystem::IRayQueryImp::getRay() const
{
	// TODO: insert return statement here
	return mRay;
}
