#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSUISystem;

NSDevilX::NSUISystem::CRenderable::SRenderGeometry::SRenderGeometry()
	:mGeometry(nullptr)
{
	mGeometry=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry("UISystem");
}

NSDevilX::NSUISystem::CRenderable::SRenderGeometry::~SRenderGeometry()
{
	NSRenderSystem::getSystem()->queryInterface_IResourceManager()->destroyGeometry(mGeometry);
}

UInt32 NSDevilX::NSUISystem::CRenderable::SRenderGeometry::allocRectangle()
{
	UInt32 ret=-1;
	if(mFreeIndexList.empty())
	{
		ret=static_cast<UInt32>(mPositions.size());
		for(auto i=0;i<4;++i)
		{
			mPositions.push_back(CFloat3(1000000.0f));
			mTextureCoords.push_back(CFloat2::sZero);
			mDiffuses.push_back(CColour(CColour::sZero).rgba8());
		}
		mGeometry->getVertexBuffer()->setCount(ret);
		mGeometry->getVertexBuffer()->setPositions(&mPositions[0]);
		mGeometry->getVertexBuffer()->setTextureCoords(&mTextureCoords[0]);
		mGeometry->getVertexBuffer()->setDiffuses(&mDiffuses[0]);
	}
	else
	{
		ret=mFreeIndexList.back();
		mFreeIndexList.pop_back();
	}
	return ret;
}

Void NSDevilX::NSUISystem::CRenderable::SRenderGeometry::freeRectangle(UInt32 vertexIndex)
{
	mFreeIndexList.push_back(vertexIndex);
	for(auto i=0;i<4;++i)
	{
		mPositions[vertexIndex+i]=CFloat3(1000000.0f);
		mTextureCoords[vertexIndex+i]=CFloat2::sZero;
		mDiffuses[vertexIndex+i]=CColour(CColour::sZero).rgba8();
	}
	mGeometry->getVertexBuffer()->updatePositions(vertexIndex,4);
	mGeometry->getVertexBuffer()->updateTextureCoords(vertexIndex,4);
	mGeometry->getVertexBuffer()->updateDiffuses(vertexIndex,4);
}

NSDevilX::NSUISystem::CRenderable::CRenderable(const CImage * img)
	:mImage(img)
	,mGeometry(nullptr)
{
	mGeometry=DEVILX_NEW SRenderGeometry();
}

NSDevilX::NSUISystem::CRenderable::~CRenderable()
{
	DEVILX_DELETE(mGeometry);
}
