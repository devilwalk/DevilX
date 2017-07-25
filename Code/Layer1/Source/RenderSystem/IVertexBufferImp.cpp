#include "Precompiler.h"
using namespace NSDevilX;
using namespace NSRenderSystem;

NSDevilX::NSRenderSystem::IVertexBufferImp::IVertexBufferImp()
	:mCount(0)
{
	memset(&mBuffers[0],0,mBuffers.size()*sizeof(mBuffers[0]));
	static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->notify(IResourceManagerImp::EMessage_VertexBufferCreate,this);
}

NSDevilX::NSRenderSystem::IVertexBufferImp::~IVertexBufferImp()
{
	if(!ISystemImp::getSingleton().isExit())
	{
		for(auto buffer:mBuffers)
			static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(buffer);
		static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->notify(IResourceManagerImp::EMessage_VertexBufferDestroy,this);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setCount(UInt32 count)
{
	if(count!=getCount())
	{
		mCount=count;
		for(UInt32 i=0;i<EBufferType_Count;++i)
		{
			auto buffer=getBuffer(i);
			if(buffer)
			{
				buffer->setSize(getCount()*getStride(i));
			}
		}
	}
}

UInt32 NSDevilX::NSRenderSystem::IVertexBufferImp::getCount() const
{
	return mCount;
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setPositions(const CFloat3 * positions)
{
	const Boolean old_enable=nullptr!=getPositions();
	const Boolean new_enable=nullptr!=positions;
	const Boolean enable_change=old_enable!=new_enable;
	if(enable_change)
	{
		notify(EMessage_BeginPositionEnableChange);
		if(new_enable)
		{
			mBuffers[EBufferType_Position]=static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->createVertexBuffer();
			getBuffer(EBufferType_Position)->setSize(getCount()*getStride(EBufferType_Position));
			getBuffer(EBufferType_Position)->setDatas(positions);
		}
		else
		{
			static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(getBuffer(EBufferType_Position));
			mBuffers[EBufferType_Position]=nullptr;
		}
		notify(EMessage_EndPositionEnableChange);
	}
	else
	{
		getBuffer(EBufferType_Position)->setDatas(positions);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updatePositions(UInt32 offset,UInt32 count)
{
	_updateBuffer(EBufferType_Position,offset,count);
}

const CFloat3 * NSDevilX::NSRenderSystem::IVertexBufferImp::getPositions() const
{
	return _getData<CFloat3>(EBufferType_Position);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setNormals(const CFloat3 * normals)
{
	const Boolean old_enable=nullptr!=getNormals();
	const Boolean new_enable=nullptr!=normals;
	const Boolean enable_change=old_enable!=new_enable;
	if(enable_change)
	{
		notify(EMessage_BeginNormalEnableChange);
		if(new_enable)
		{
			mBuffers[EBufferType_Normal]=static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->createVertexBuffer();
			getBuffer(EBufferType_Normal)->setSize(getCount()*getStride(EBufferType_Normal));
			getBuffer(EBufferType_Normal)->setDatas(normals);
		}
		else
		{
			static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(getBuffer(EBufferType_Normal));
			mBuffers[EBufferType_Normal]=nullptr;
		}
		notify(EMessage_EndNormalEnableChange);
	}
	else
	{
		getBuffer(EBufferType_Normal)->setDatas(normals);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateNormals(UInt32 offset,UInt32 count)
{
	_updateBuffer(EBufferType_Normal,offset,count);
}

const CFloat3 * NSDevilX::NSRenderSystem::IVertexBufferImp::getNormals() const
{
	return _getData<CFloat3>(EBufferType_Normal);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setTangents(const CFloat3 * tangents)
{
	const Boolean old_enable=nullptr!=getTangents();
	const Boolean new_enable=nullptr!=tangents;
	const Boolean enable_change=old_enable!=new_enable;
	if(enable_change)
	{
		notify(EMessage_BeginTangentEnableChange);
		if(new_enable)
		{
			mBuffers[EBufferType_Tangent]=static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->createVertexBuffer();
			getBuffer(EBufferType_Tangent)->setSize(getCount()*getStride(EBufferType_Tangent));
			getBuffer(EBufferType_Tangent)->setDatas(tangents);
		}
		else
		{
			static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(getBuffer(EBufferType_Tangent));
			mBuffers[EBufferType_Tangent]=nullptr;
		}
		notify(EMessage_EndTangentEnableChange);
	}
	else
	{
		getBuffer(EBufferType_Tangent)->setDatas(tangents);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateTangents(UInt32 offset,UInt32 count)
{
	_updateBuffer(EBufferType_Tangent,offset,count);
}

const CFloat3 * NSDevilX::NSRenderSystem::IVertexBufferImp::getTangents() const
{
	return _getData<CFloat3>(EBufferType_Tangent);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setTextureCoords(const CFloat2 * uvs,IEnum::ETextureCoord index)
{
	const Boolean old_enable=nullptr!=getTextureCoords(index);
	const Boolean new_enable=nullptr!=uvs;
	const Boolean enable_change=old_enable!=new_enable;
	if(enable_change)
	{
		switch(index)
		{
		case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_0:
			notify(EMessage_BeginTextureCoord0EnableChange);
			break;
		case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_1:
			notify(EMessage_BeginTextureCoord1EnableChange);
			break;
		}
		if(new_enable)
		{
			mBuffers[EBufferType_TextureCoord0+index]=static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->createVertexBuffer();
			getBuffer(EBufferType_TextureCoord0+index)->setSize(getCount()*getStride(EBufferType_TextureCoord0+index));
			getBuffer(EBufferType_TextureCoord0+index)->setDatas(uvs);
		}
		else
		{
			static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(getBuffer(EBufferType_TextureCoord0+index));
			mBuffers[EBufferType_TextureCoord0+index]=nullptr;
		}
		switch(index)
		{
		case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_0:
			notify(EMessage_EndTextureCoord0EnableChange);
			break;
		case NSDevilX::NSRenderSystem::IEnum::ETextureCoord_1:
			notify(EMessage_EndTextureCoord1EnableChange);
			break;
		}
	}
	else
	{
		getBuffer(EBufferType_TextureCoord0+index)->setDatas(uvs);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateTextureCoords(UInt32 offset,UInt32 count,IEnum::ETextureCoord index)
{
	_updateBuffer(EBufferType_TextureCoord0+index,offset,count);
}

const CFloat2 * NSDevilX::NSRenderSystem::IVertexBufferImp::getTextureCoords(IEnum::ETextureCoord index) const
{
	return _getData<CFloat2>(EBufferType_TextureCoord0+index);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setBlendWeights(const CFloat4 * blendWeights)
{
	const Boolean old_enable=nullptr!=getBlendWeights();
	const Boolean new_enable=nullptr!=blendWeights;
	const Boolean enable_change=old_enable!=new_enable;
	if(enable_change)
	{
		notify(EMessage_BeginBlendWeightEnableChange);
		if(new_enable)
		{
			mBuffers[EBufferType_BlendWeight]=static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->createVertexBuffer();
			getBuffer(EBufferType_BlendWeight)->setSize(getCount()*getStride(EBufferType_BlendWeight));
			getBuffer(EBufferType_BlendWeight)->setDatas(blendWeights);
		}
		else
		{
			static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(getBuffer(EBufferType_BlendWeight));
			mBuffers[EBufferType_BlendWeight]=nullptr;
		}
		notify(EMessage_EndBlendWeightEnableChange);
	}
	else
	{
		getBuffer(EBufferType_BlendWeight)->setDatas(blendWeights);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateBlendWeights(UInt32 offset,UInt32 count)
{
	_updateBuffer(EBufferType_BlendWeight,offset,count);
}

const CFloat4 * NSDevilX::NSRenderSystem::IVertexBufferImp::getBlendWeights() const
{
	return _getData<CFloat4>(EBufferType_BlendWeight);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setBlendIndices(const UInt8 * blendIndices)
{
	const Boolean old_enable=nullptr!=getBlendIndices();
	const Boolean new_enable=nullptr!=blendIndices;
	const Boolean enable_change=old_enable!=new_enable;
	if(enable_change)
	{
		notify(EMessage_BeginBlendIndexEnableChange);
		if(new_enable)
		{
			mBuffers[EBufferType_BlendIndex]=static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->createVertexBuffer();
			getBuffer(EBufferType_BlendIndex)->setSize(getCount()*getStride(EBufferType_BlendIndex));
			getBuffer(EBufferType_BlendIndex)->setDatas(blendIndices);
		}
		else
		{
			static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(getBuffer(EBufferType_BlendIndex));
			mBuffers[EBufferType_BlendIndex]=nullptr;
		}
		notify(EMessage_EndBlendIndexEnableChange);
	}
	else
	{
		getBuffer(EBufferType_BlendIndex)->setDatas(blendIndices);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateBlendIndices(UInt32 offset,UInt32 count)
{
	_updateBuffer(EBufferType_BlendIndex,offset,count);
}

const UInt8 * NSDevilX::NSRenderSystem::IVertexBufferImp::getBlendIndices() const
{
	return _getData<UInt8>(EBufferType_BlendIndex);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::setDiffuses(const RGBA * colours)
{
	const Boolean old_enable=nullptr!=getDiffuses();
	const Boolean new_enable=nullptr!=colours;
	const Boolean enable_change=old_enable!=new_enable;
	if(enable_change)
	{
		notify(EMessage_BeginDiffuseEnableChange);
		if(new_enable)
		{
			mBuffers[EBufferType_Diffuse]=static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->createVertexBuffer();
			getBuffer(EBufferType_Diffuse)->setSize(getCount()*getStride(EBufferType_Diffuse));
			getBuffer(EBufferType_Diffuse)->setDatas(colours);
		}
		else
		{
			static_cast<IResourceManagerImp*>(ISystemImp::getSingleton().queryInterface_IResourceManager())->destroyInternalBuffer(getBuffer(EBufferType_Diffuse));
			mBuffers[EBufferType_Diffuse]=nullptr;
		}
		notify(EMessage_EndDiffuseEnableChange);
	}
	else
	{
		getBuffer(EBufferType_Diffuse)->setDatas(colours);
	}
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::updateDiffuses(UInt32 offset,UInt32 count)
{
	_updateBuffer(EBufferType_Diffuse,offset,count);
}

const RGBA * NSDevilX::NSRenderSystem::IVertexBufferImp::getDiffuses() const
{
	return _getData<RGBA>(EBufferType_Diffuse);
}

Void NSDevilX::NSRenderSystem::IVertexBufferImp::_updateBuffer(UInt32 index,UInt32 offset,UInt32 count)
{
	if(getBuffer(index))
		getBuffer(index)->updateData(offset*getStride(index),count*getStride(index));
}
