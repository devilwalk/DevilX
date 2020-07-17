#pragma once
#include "CommonBoundingTreeNode.h"
#include "CommonBounding.h"
#include "CommonType.h"
namespace NSDevilX
{
	class COctreeNode
		:public TBoundingTreeNode<CBoundingBox>
	{
	public:
		const static UInt32 sChildrenIndex[];
	protected:
	public:
		using TBoundingTreeNode<CBoundingBox>::CBoundingTreeNode;
		virtual ~COctreeNode()
		{}
		template<class containerT>
		Void get(const CPlaneBoundedVolume & pbv,containerT * visible,containerT * unvisible)const
		{
			const auto ct=pbv.intersect(mBoundingBox);
			if(CBoundingBox::EIntersect_Contain==ct)
			{
				if(visible)
				{
					getAll<containerT>(*visible);
				}
			}
			else if(CBoundingBox::EIntersect_Intersect==ct)
			{
				if(visible)
				{
					visible->insert(visible->end(),this);
					if(mChildren)
					{
                        for(auto child:*mChildren)
                        {
                            if(child)
                                static_cast<COctreeNode*>(child)->get(pbv,visible,unvisible);
                        }
					}
				}
			}
			else if(CBoundingBox::EIntersect_None==ct)
			{
				if(unvisible)
				{
					getAll<containerT>(*unvisible);
				}
			}
		}
	protected:
		//得到point属于的child,-1表示不属于child
		/*UInt32 _getChildIndex(DirectX::FXMVECTOR point)const
		{
			DirectX::XMVECTOR delta_vec=point-mBoundingBox.Center;
			if(DirectX::XMVector3Equal(delta_vec,DirectX::XMVectorZero()))
				return -1;
			DirectX::XMVECTOR test_value=DirectX::XMVectorGreaterOrEqual(delta_vec,DirectX::XMVectorZero());
			unsigned short child_array_index[3];
			child_array_index[0]=DirectX::XMVectorGetIntX(test_value)?0:1;
			child_array_index[1]=DirectX::XMVectorGetIntY(test_value)?0:1;
			child_array_index[2]=DirectX::XMVectorGetIntZ(test_value)?0:1;
			return sChildrenIndex[child_array_index[0]+child_array_index[1]*2+child_array_index[2]*4];
		}
		//得到aabb属于的child,-1表示不属于child
		UInt32 _getChildIndex(const DirectX::BoundingBox & aabb)const
		{
			assert(DirectX::DISJOINT!=mBoundingBox.Contains(aabb));
			UInt32 ret=-1;
			DirectX::XMVECTOR delta_vec=aabb.Center-mBoundingBox.Center;
			DirectX::XMVECTOR delta_size=DirectX::XMVectorAbs(delta_vec);
			DirectX::XMVECTOR half_size=aabb.Extents*CFloat3(0.5f);
			if(DirectX::XMVector3Greater(delta_size,half_size))
			{
				ret=_getChildIndex(CFloat3(aabb.Center));
			}
			return ret;
		}*/
	};
}
