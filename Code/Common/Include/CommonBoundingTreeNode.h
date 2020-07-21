#pragma once
#include "CommonNode.h"
#include "CommonBounding.h"
#include "CommonResourceContainer.h"
namespace NSDevilX
{
	template<class TBoundingVolume>
	class TBoundingTreeNode
		:public TNode<TResourcePtrVector<TBoundingTreeNode<TBoundingVolume> > >
	{
	protected:
		TBoundingVolume mBoundingVolume;
	public:
		TBoundingTreeNode(const TBoundingVolume& bv,TBoundingTreeNode* parent)
			:mBoundingVolume(bv)
		{
			setParent(parent);
		}
		virtual ~TBoundingTreeNode()
		{
			TNode<TResourcePtrVector<TBoundingTreeNode<TBoundingVolume> > >::destroyChildren();
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