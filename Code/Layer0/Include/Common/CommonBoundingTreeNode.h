#pragma once
#include "CommonNode.h"
#include "CommonBounding.h"
namespace NSDevilX
{
	class CBoundingTreeNode
		:public CNode
	{
	protected:
		DirectX::BoundingBox mBoundingBox;
	public:
		CBoundingTreeNode(const DirectX::BoundingBox & aabb,CBoundingTreeNode * parent)
			:mBoundingBox(aabb)
		{
			setParent(parent);
		}
		virtual ~CBoundingTreeNode()
		{
			destroyChildren();
		}
		const DirectX::BoundingBox & getBoundingBox()const
		{
			return mBoundingBox;
		}
		DirectX::BoundingBox getChildBoudingBox(UInt32 index)const
		{
			DirectX::BoundingBox ret;
			ret.Center=CFloat3(DirectX::g_BoxOffset[index]*0.5f+mBoundingBox.Center);
			ret.Extents=CFloat3(CFloat3(mBoundingBox.Extents)*0.5f);
			return ret;
		}

	};
	class CQuadTreeNode
		:public CBoundingTreeNode
	{
	public:
		const static UInt32 sChildrenIndex[];
	public:
		using CBoundingTreeNode::CBoundingTreeNode;
		virtual ~CQuadTreeNode()
		{}
		Boolean childContains(const DirectX::BoundingBox & aabb)const
		{
			assert(DirectX::DISJOINT!=mBoundingBox.Contains(aabb));
			DirectX::XMVECTOR delta_size=DirectX::XMVectorAbs(aabb.Center-mBoundingBox.Center);
			DirectX::XMVECTOR half_size=aabb.Extents*CFloat3(0.5f);
			return DirectX::XMVector2Greater(delta_size,half_size);
		}
	};
}