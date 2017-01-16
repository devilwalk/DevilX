#pragma once
#include "CommonType.h"
#include "CommonSTL.h"
#include "CommonMessageMode.h"
namespace NSDevilX
{
	class CNode
		:public CMessageNotifier
	{
	public:
		enum EMessage
		{
			EMessage_BeginParentChange,
			EMessage_EndParentChange,
			EMessage_BeginChildAdd,
			EMessage_EndChildAdd,
			EMessage_BeginChildRemove,
			EMessage_EndChildRemove
		};
		typedef TSet<CNode*> Children;
	protected:
		CNode * mParent;
		Children * mChildren;
	public:
		CNode();
		virtual ~CNode();
		Void setParent(CNode * node);
		CNode * getParent()const
		{
			return mParent;
		}
		Void addChild(CNode * node);
		Void removeChild(CNode * node);
		Boolean hasChild(CNode * node)
		{
			return mChildren&&_getChildren().has(node);
		}
		Void clearChildren();
		Void destroyChildren();
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
		Children & _getChildren();
		virtual Void _beginAddChild(CNode * node);
		virtual Void _endAddChild(CNode * node);
		virtual Void _beginRemoveChild(CNode * node);
		virtual Void _endRemoveChild(CNode * node);
	};
}
