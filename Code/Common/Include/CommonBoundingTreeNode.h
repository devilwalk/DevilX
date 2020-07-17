#pragma once
#include "CommonNode.h"
#include "CommonBounding.h"
#include "CommonResourceContainer.h"
namespace NSDevilX
{
	template<class TBoundingVolume>
	class TBoundingTreeNode
		:public TNode<TResourcePtrVector<CBoundingTreeNode> >
	{
	protected:
		TBoundingVolume mBoundingVolume;
	public:
		TBoundingTreeNode(const TBoundingVolume& bv,CBoundingTreeNode * parent)
			:mBoundingVolume(bv)
		{
			setParent(parent);
		}
		virtual ~TBoundingTreeNode()
		{
			destroyChildren();
		}
		const auto & getBoundingVolume()const
		{
			return mBoundingVolume;
		}

	};
	class CQuadTreeNode
		:public TBoundingTreeNode<CBoundingBox>
	{
	public:
		using TBoundingTreeNode<CBoundingBox>::TBoundingTreeNode;
		virtual ~CQuadTreeNode()
		{}
	};
}