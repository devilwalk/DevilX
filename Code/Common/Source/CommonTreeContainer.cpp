#include "Precompiler.h"
using namespace NSDevilX;

NSDevilX::C3DTreeNode::C3DTreeNode(const CRange3I & range)
	:TTreeNode<CRange3I>(range)
{}

NSDevilX::C3DTreeNode::~C3DTreeNode()
{}

Void NSDevilX::C3DTreeNode::fillChildrenData()
{
	auto const & range=static_cast<SData*>(mData)->mRange;
	static_cast<SData*>(mData)->mChildren->resize(8);
	CRange3I ranges[8];
	CInt3 half_extend=(range.getMax()-range.getMin()+CMath::sInt3_One)/2;
	ranges[0]=CRange3I(range.getMin(),range.getMin()+half_extend-CMath::sInt3_One);
	ranges[1]=CRange3I(CInt3(range.getMin().x,range.getMin().y+half_extend.y-1,range.getMin().z),CInt3(range.getMin().x+half_extend.x-1,range.getMax().y,range.getMin().z+half_extend.z-1));
	ranges[2]=CRange3I(CInt3(range.getMin().x,range.getMin().y,range.getMin().z+half_extend.z-1),CInt3(range.getMin().x+half_extend.x-1,range.getMin().y+half_extend.y-1,range.getMax().z));
	ranges[3]=CRange3I(CInt3(range.getMin().x,range.getMin().y+half_extend.y-1,range.getMin().z+half_extend.z-1),CInt3(range.getMin().x+half_extend.x-1,range.getMax().y,range.getMax().z));
	ranges[4]=CRange3I(CInt3(range.getMin().x+half_extend.x-1,range.getMin().y,range.getMin().z),CInt3(range.getMax().x,range.getMin().y+half_extend.y-1,range.getMin().z+half_extend.z-1));
	ranges[5]=CRange3I(CInt3(range.getMin().x+half_extend.x-1,range.getMin().y+half_extend.y-1,range.getMin().z),CInt3(range.getMax().x,range.getMax().y,range.getMin().z+half_extend.z-1));
	ranges[6]=CRange3I(CInt3(range.getMin().x+half_extend.x-1,range.getMin().y,range.getMin().z+half_extend.y-1),CInt3(range.getMax().x,range.getMin().y+half_extend.z-1,range.getMax().z));
	ranges[7]=CRange3I(range.getMin()+half_extend-CMath::sInt3_One,range.getMax());
	if(half_extend==CMath::sInt3_One)
	{
		for(int i=0;i<8;++i)
		{
			(*static_cast<SData*>(mData)->mChildren)[i]=new C3DTreeLeaf(ranges[i].getMin());
		}
	}
	else
	{
		for(int i=0;i<8;++i)
		{
			(*static_cast<SData*>(mData)->mChildren)[i]=new C3DTreeNode(ranges[i]);
		}
	}
}

NSDevilX::C3DTreeLeaf::C3DTreeLeaf(const CInt3 & position)
	:TTreeLeaf<CRange3I,CInt3>(position)
{}

NSDevilX::C3DTreeLeaf::~C3DTreeLeaf()
{}
