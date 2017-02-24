#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSDevilCraft;

NSDevilX::NSDevilCraft::CEntityPlayer::CEntityPlayer(CPlayer * player)
	:CEntity("Player",player->getScene())
	,mPlayer(player)
{}

NSDevilX::NSDevilCraft::CEntityPlayer::~CEntityPlayer()
{}

NSDevilX::NSDevilCraft::CPlayer::SActor::SActor(CPlayer * player)
	:mPlayer(player)
	,mIsJump(False)
{
	auto config=CApp::getSingleton().getInputConfigManager()->getConfig("DefaultPlayer");
	if(!config)
	{
		config=CApp::getSingleton().getInputConfigManager()->createConfig("DefaultPlayer");
		config->setKeyDown(NSInputSystem::IEnum::EKeyType_W,EType_MoveForward);
		config->setKeyDown(NSInputSystem::IEnum::EKeyType_S,EType_MoveBackward);
		config->setKeyDown(NSInputSystem::IEnum::EKeyType_A,EType_MoveLeft);
		config->setKeyDown(NSInputSystem::IEnum::EKeyType_D,EType_MoveRight);
		config->setKeyDown(NSInputSystem::IEnum::EKeyType_SPACE,EType_Jump);
	}
	setInputConfig(config);
}

Void NSDevilX::NSDevilCraft::CPlayer::SActor::addAction(UInt32 action)
{
	switch(action)
	{
	case EType_Jump:
		if((!mIsJump)&&(!mPlayer->isJump()))
		{
			mIsJump=True;
			CActor::addAction(action);
		}
		break;
	default:
		CActor::addAction(action);
	}
}

NSDevilX::NSDevilCraft::CPlayer::CPlayer(const String & name,CScene * scene)
	:mScene(scene)
	,mEntity(nullptr)
	,mActor(nullptr)
	,mRenderCamera(nullptr)
{
	mEntity=DEVILX_NEW CEntityPlayer(this);
	mActor=DEVILX_NEW SActor(this);
	mRenderCamera=getScene()->getRenderScene()->createCamera(name);
	mRenderCamera->setFarClipPlane(1000.0f);
	mRenderCamera->setNearClipPlane(1.0f);
	mRenderCamera->setProjectionType(NSRenderSystem::IEnum::EProjectionType_Perspective);
	mRenderCamera->queryInterface_IPerspectiveProperty()->setFov(CDegree(45.0f));
	mRenderCamera->queryInterface_IPerspectiveProperty()->setAspectRatio(static_cast<Float>(CApp::getSingleton().getWindow()->getSize().x)/static_cast<Float>(CApp::getSingleton().getWindow()->getSize().y));
}

NSDevilX::NSDevilCraft::CPlayer::~CPlayer()
{
	DEVILX_DELETE(mEntity);
	DEVILX_DELETE(mActor);
	getScene()->getRenderScene()->destroyCamera(mRenderCamera);
}

Void NSDevilX::NSDevilCraft::CPlayer::addAction(SActor::EType action)
{
	mActor->addAction(action);
}

Void NSDevilX::NSDevilCraft::CPlayer::update()
{
}