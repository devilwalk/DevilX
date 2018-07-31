#pragma once
#include "Type.h"
#include "STL.h"
#include "Any.h"
namespace NSDevilX
{
	namespace NSCore
	{
		template<class childrenContainerT>
		class TNode
		{
		public:
			typedef childrenContainerT Children;
		protected:
			TNode*mParent;
			Children * mChildren;
			CAny mUserData;
		public:
			TNode(TNode * parent=nullptr)
				:mParent(parent)
				,mChildren(nullptr)
			{}
			virtual ~TNode()
			{
				destroyChildren();
			}
			Void setUserData(const CAny & data)
			{
				mUserData=data;
			}
			template<typename T>
			const T & getUserData()const
			{
				return mUserData.get<T>();
			}
			Void setParent(TNode * node)
			{
				if(node!=mParent)
				{
					mParent=node;
				}
			}
			TNode * getParent()const
			{
				return mParent;
			}
			Void addChild(TNode * node)
			{
				assert(!hasChild(node));
				if(_filterAddChild(node))
				{
					_getChildren().insert(_getChildren().end(),node);
					node->setParent(this);
					_notifyAddChild(node);
				}
			}
			Void removeChild(TNode * node)
			{
				assert(hasChild(node));
				if(_filterRemoveChild(node))
				{
					mChildren->remove(node);
					node->setParent(nullptr);
					_notifyRemoveChild(node);
				}
			}
			Boolean hasChild(TNode * node)const
			{
				return mChildren&&mChildren->has(node);
			}
			Void clearChildren()
			{
				if(mChildren)
				{
					mChildren->clear();
				}
			}
			Void destroyChildren()
			{
				DEVILX_DELETE(mChildren);
			}
			template<typename containerT>
			void getAll(containerT & ret)const
			{
				ret.insert(ret.end(),this);
				if(mChildren)
				{
					for(auto child:*mChildren)
					{
						child->getAll<containerT>(ret);
					}
				}
			}
		protected:
			Children&_getChildren()
			{
				// TODO: insert return statement here
				if(!mChildren)
					mChildren=DEVILX_NEW Children;
				return *mChildren;
			}
			virtual Boolean _filterAddChild(TNode * node)
			{
				return true;
			}
			virtual Void _notifyAddChild(TNode * node)
			{
			}
			virtual Boolean _filterRemoveChild(TNode * node)
			{
				return true;
			}
			virtual Void _notifyRemoveChild(TNode * node)
			{
			}
		};
	}
}
