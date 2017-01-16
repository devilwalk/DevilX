#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IVertexBufferImp::IVertexBufferImp()
	:mCount(0)
	,mPositions(nullptr)
	,mNormals(nullptr)
	,mTangents(nullptr)
	,mBlendWeights(nullptr)
	,mBlendIndices(nullptr)
	,mDiffuses(nullptr)
{
	memset(mTextureCoords,0,sizeof(mTextureCoords));
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->notify(IResourceManagerImp::EMessage_VertexBufferCreate,this);
}

NSDevilX::NSRenderSystem::IVertexBufferImp::~IVertexBufferImp()
{
	if(!ISystemImp::getSingleton().isExit())
		static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->notify(IResourceManagerImp::EMessage_VertexBufferDestroy,this);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::_preProcessDirtyFlagAdd(UInt32 flagIndex)
{
	notify(EMessage_BeginDirtyFlagAdd,&flagIndex);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::_postProcessDirtyFlagAdd(UInt32 flagIndex)
{
	notify(EMessage_EndDirtyFlagAdd,&flagIndex);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setCount(UInt32 count)
{
	if(count!=getCount())
	{
		mCount=count;
		addDirtyFlag(EDirtyFlag_Count);
	}
}

UInt32 NSDevilX::NSRenderSystem::IVertexBufferImp::getCount() const
{
	return mCount;
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setPositions(const CFloat3 * positions)
{
	if(positions!=mPositions)
	{
		mPositions=positions;
		addDirtyFlag(EDirtyFlag_Position);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updatePositions()
{
	addDirtyFlag(EDirtyFlag_Position);
}

const CFloat3 * NSDevilX::NSRenderSystem::IVertexBufferImp::getPositions() const
{
	return mPositions;
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setNormals(const CFloat3 * normals)
{
	if(normals!=mNormals)
	{
		const Boolean old_enable=nullptr!=getNormals();
		const Boolean new_enable=nullptr!=normals;
		const Boolean enable_change=old_enable!=new_enable;
		if(enable_change)
			notify(EMessage_BeginNormalEnableChange);
		mNormals=normals;
		addDirtyFlag(EDirtyFlag_Normal);
		if(enable_change)
			notify(EMessage_EndNormalEnableChange);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateNormals()
{
	addDirtyFlag(EDirtyFlag_Normal);
}

const CFloat3 * NSDevilX::NSRenderSystem::IVertexBufferImp::getNormals() const
{
	return mNormals;
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setTangents(const CFloat3 * tangents)
{
	if(tangents!=mTangents)
	{
		const Boolean old_enable=nullptr!=getTangents();
		const Boolean new_enable=nullptr!=tangents;
		const Boolean enable_change=old_enable!=new_enable;
		if(enable_change)
			notify(EMessage_BeginTangentEnableChange);
		mTangents=tangents;
		addDirtyFlag(EDirtyFlag_Tangent);
		if(enable_change)
			notify(EMessage_EndTangentEnableChange);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateTangents()
{
	addDirtyFlag(EDirtyFlag_Tangent);
}

const CFloat3 * NSDevilX::NSRenderSystem::IVertexBufferImp::getTangents() const
{
	return mTangents;
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setTextureCoords(const CFloat2 * uvs,IEnum::ETextureCoord index)
{
	if(uvs!=getTextureCoords(index))
	{
		const Boolean old_enable=nullptr!=getTextureCoords(index);
		const Boolean new_enable=nullptr!=uvs;
		const Boolean enable_change=old_enable!=new_enable;
		if(enable_change)
			switch(index)
			{
			case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_0:
				notify(EMessage_BeginTextureCoord0EnableChange);
				break;
			case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_1:
				notify(EMessage_BeginTextureCoord1EnableChange);
				break;
			}
		mTextureCoords[index]=uvs;
		switch(index)
		{
		case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_0:
			addDirtyFlag(EDirtyFlag_TextureCoord0);
			notify(EMessage_EndTextureCoord0EnableChange);
			break;
		case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_1:
			addDirtyFlag(EDirtyFlag_TextureCoord1);
			notify(EMessage_EndTextureCoord1EnableChange);
			break;
		}
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateTextureCoords(IEnum::ETextureCoord index)
{
	switch(index)
	{
	case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_0:
		addDirtyFlag(EDirtyFlag_TextureCoord0);
		break;
	case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_1:
		addDirtyFlag(EDirtyFlag_TextureCoord1);
		break;
	}
}

const CFloat2 * NSDevilX::NSRenderSystem::IVertexBufferImp::getTextureCoords(IEnum::ETextureCoord index) const
{
	return mTextureCoords[index];
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setBlendWeights(const CFloat4 * blendWeights)
{
	if(blendWeights!=mBlendWeights)
	{
		mBlendWeights=blendWeights;
		addDirtyFlag(EDirtyFlag_BlendWeight);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateBlendWeights()
{
	addDirtyFlag(EDirtyFlag_BlendWeight);
}

const CFloat4 * NSDevilX::NSRenderSystem::IVertexBufferImp::getBlendWeights() const
{
	return mBlendWeights;
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setBlendIndices(const UInt8 * blendIndices)
{
	if(blendIndices!=mBlendIndices)
	{
		mBlendIndices=blendIndices;
		addDirtyFlag(EDirtyFlag_BlendIndex);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateBlendIndices()
{
	addDirtyFlag(EDirtyFlag_BlendIndex);
}

const UInt8 * NSDevilX::NSRenderSystem::IVertexBufferImp::getBlendIndices() const
{
	return mBlendIndices;
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setDiffuses(const RGBA * colours)
{
	if(getDiffuses()!=colours)
	{
		const Boolean old_enable=nullptr!=getDiffuses();
		const Boolean new_enable=nullptr!=colours;
		const Boolean enable_change=old_enable!=new_enable;
		if(enable_change)
			notify(EMessage_BeginDiffuseEnableChange);
		mDiffuses=colours;
		addDirtyFlag(EDirtyFlag_Diffuse);
		if(enable_change)
			notify(EMessage_EndDiffuseEnableChange);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateDiffuses()
{
	addDirtyFlag(EDirtyFlag_Diffuse);
}

const RGBA * NSDevilX::NSRenderSystem::IVertexBufferImp::getDiffuses() const
{
	return mDiffuses;
}
