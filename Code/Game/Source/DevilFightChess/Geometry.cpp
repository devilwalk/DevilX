#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSFightChess;

NSDevilX::NSFightChess::CGeometry::CGeometry()
	:mRenderGeometry(nullptr)
{}

NSDevilX::NSFightChess::CGeometry::~CGeometry()
{
	if(getRenderGeometry())
		NSRenderSystem::getSystem()->queryInterface_IResourceManager()->destroyGeometry(getRenderGeometry());
}

NSDevilX::NSFightChess::CGrasses::CGrasses()
{
	const UInt32 grass_row=10;
	const UInt32 grass_col=10;
	for(UInt32 row=0;row<grass_row;++row)
	{
		for(UInt32 col=0;col<grass_col;++col)
		{
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+0);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+1);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+2);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+2);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+1);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+3);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+4);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+5);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+6);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+6);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+5);
			mIndices.push_back(static_cast<UInt32>(mPositions.size())+7);
			CFloat3 grass_pos=CFloat3(col+0.5f,0,row+0.5f)*0.1f;
			mPositions.push_back(grass_pos-CFloat3::sUnitX+CFloat3::sUnitY);
			mPositions.push_back(grass_pos+CFloat3::sUnitX+CFloat3::sUnitY);
			mPositions.push_back(grass_pos-CFloat3::sUnitX);
			mPositions.push_back(grass_pos+CFloat3::sUnitX);
			mPositions.push_back(grass_pos-CFloat3::sUnitZ+CFloat3::sUnitY);
			mPositions.push_back(grass_pos+CFloat3::sUnitZ+CFloat3::sUnitY);
			mPositions.push_back(grass_pos-CFloat3::sUnitZ);
			mPositions.push_back(grass_pos+CFloat3::sUnitZ);
			mNormals.push_back(CFloat3::sUnitY);
			mNormals.push_back(CFloat3::sUnitY);
			mNormals.push_back(-CFloat3::sUnitX);
			mNormals.push_back(CFloat3::sUnitX);
			mNormals.push_back(CFloat3::sUnitY);
			mNormals.push_back(CFloat3::sUnitY);
			mNormals.push_back(-CFloat3::sUnitZ);
			mNormals.push_back(CFloat3::sUnitZ);
			mTextureCoords.push_back(CFloat2::sZero);
			mTextureCoords.push_back(CFloat2(1.0f,0.0f));
			mTextureCoords.push_back(CFloat2(0.0f,1.0f));
			mTextureCoords.push_back(CFloat2::sOne);
			mTextureCoords.push_back(CFloat2::sZero);
			mTextureCoords.push_back(CFloat2(1.0f,0.0f));
			mTextureCoords.push_back(CFloat2(0.0f,1.0f));
			mTextureCoords.push_back(CFloat2::sOne);
		}
	}
	mRenderGeometry=NSRenderSystem::getSystem()->queryInterface_IResourceManager()->createGeometry("Grasses");
	mRenderGeometry->getVertexBuffer()->setCount(static_cast<UInt32>(mPositions.size()));
	mRenderGeometry->getVertexBuffer()->setPositions(&mPositions[0]);
	mRenderGeometry->getVertexBuffer()->setNormals(&mNormals[0]);
	mRenderGeometry->getVertexBuffer()->setTextureCoords(&mTextureCoords[0]);
	mRenderGeometry->getIndexBuffer()->setCount(static_cast<UInt32>(mIndices.size()));
	mRenderGeometry->getIndexBuffer()->setIndices(&mIndices[0]);
}

NSDevilX::NSFightChess::CGrasses::~CGrasses()
{}
