#include "Precompiler.h"
using namespace NSDevilX;
NSDevilX::CNode::CNode()
	:mParent(nullptr)
	,mChildren(nullptr)
{}

NSDevilX::CNode::~CNode()
{}

Void NSDevilX::CNode::setParent(CNode * node)
{
	if(node!=mParent)
	{
		notify(EMessage_BeginParentChange);
		mParent=node;
		notify(EMessage_EndParentChange);
	}
}

Void NSDevilX::CNode::addChild(CNode * node)
{
	if(hasChild(node))
		return;
	notify(EMessage_BeginChildAdd);
	_beginAddChild(node);
	_getChildren().insert(node);
	node->setParent(this);
	_endAddChild(node);
	notify(EMessage_EndChildAdd);
}

Void NSDevilX::CNode::removeChild(CNode * node)
{
	if(!hasChild(node))
		return;
	notify(EMessage_BeginChildRemove);
	_beginRemoveChild(node);
	_getChildren().erase(node);
	node->setParent(nullptr);
	_endRemoveChild(node);
	notify(EMessage_EndChildRemove);
}

Void NSDevilX::CNode::clearChildren()
{
	if(mChildren)
	{
		_getChildren().clear();
	}
}

Void NSDevilX::CNode::destroyChildren()
{
	DEVILX_DELETE(mChildren);
}

CNode::Children & NSDevilX::CNode::_getChildren()
{
	// TODO: insert return statement here
	if(!mChildren)
		mChildren=DEVILX_NEW Children;
	return *mChildren;
}

Void NSDevilX::CNode::_beginAddChild(CNode * node)
{
}

Void NSDevilX::CNode::_endAddChild(CNode * node)
{
}

Void NSDevilX::CNode::_beginRemoveChild(CNode * node)
{
}

Void NSDevilX::CNode::_endRemoveChild(CNode * node)
{
}
