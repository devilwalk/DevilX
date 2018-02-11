#pragma once
#include "CommonType.h"
#include "CommonSTL.h"
namespace NSDevilX
{
	template<class childrenContainerT>
	class TNode
	{
	public:
		typedef childrenContainerT Children;
	protected:
		TNode * mParent;
		Children * mChildren;
		VoidPtr mUserData;
	public:
		TNode()
			:mParent(nullptr)
			,mChildren(nullptr)
		{}

		virtual ~TNode()
		{
			destroyChildren();
		}
		Void setUserData(VoidPtr data)
		{
			mUserData=data;
		}
		VoidPtr getUserData()const
		{
			return mUserData;
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
			if(hasChild(node))
				return;
			_beginAddChild(node);
			_getChildren().insert(_getChildren().end(),node);
			node->setParent(this);
			_endAddChild(node);
		}
		Void removeChild(TNode * node)
		{
			if(!hasChild(node))
				return;
			_beginRemoveChild(node);
			_getChildren().remove(node);
			node->setParent(nullptr);
			_endRemoveChild(node);
		}
		Boolean hasChild(TNode * node)
		{
			return mChildren&&_getChildren().has(node);
		}
		Void clearChildren()
		{
			if(mChildren)
			{
				_getChildren().clear();
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
		Children & _getChildren()
		{
			// TODO: insert return statement here
			if(!mChildren)
				mChildren=DEVILX_NEW Children;
			return *mChildren;
		}
		virtual Void _beginAddChild(TNode * node){}
		virtual Void _endAddChild(TNode * node){}
		virtual Void _beginRemoveChild(TNode * node){}
		virtual Void _endRemoveChild(TNode * node){}
	};
}
