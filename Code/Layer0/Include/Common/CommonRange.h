#pragma once
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonVectorF.h"
#include "CommonVectorI.h"
namespace NSDevilX
{
	class CRange3I
		:public TBaseObject<CRange3I>
	{
	protected:
		CSInt3 mMin;
		CSInt3 mMax;
	public:
		CRange3I()
			:mMin(1,1,1)
			,mMax(0,0,0)
		{}
		CRange3I(DirectX::FXMVECTOR minPositionVec,DirectX::FXMVECTOR maxPositionVec)
			:mMin(minPositionVec)
			,mMax(maxPositionVec)
		{
		}
		~CRange3I()
		{}
		Boolean isValidate()const
		{
			return getMax()>=getMin();
		}
		Boolean isValidateX()const
		{
			return getMax().x>=getMin().x;
		}
		Boolean isValidateY()const
		{
			return getMax().y>=getMin().y;
		}
		Boolean isValidateZ()const
		{
			return getMax().z>=getMin().z;
		}
		Void setMin(DirectX::FXMVECTOR vec)
		{
			mMin=vec;
		}
		const CSInt3 & getMin()const
		{
			return mMin;
		}
		Void setMax(DirectX::FXMVECTOR vec)
		{
			mMax=vec;
		}
		const CSInt3 & getMax()const
		{
			return mMax;
		}
		Boolean merge(const CRange3I & range)
		{
			assert(isValidate()&&range.isValidate());
			const DirectX::XMVECTOR src_min_vec=getMin();
			const DirectX::XMVECTOR src_max_vec=getMax();
			const DirectX::XMVECTOR dst_min_vec=range.getMin();
			const DirectX::XMVECTOR dst_max_vec=range.getMax();
			const DirectX::XMVECTOR one_vec=CSInt3::sOne;
			const CSInt3 src_size=src_max_vec-src_min_vec+one_vec;
			const auto src_volume=src_size.x*src_size.y*src_size.z;
			const CSInt3 dst_size=dst_max_vec-dst_min_vec+one_vec;
			const auto dst_volume=dst_size.x*dst_size.y*dst_size.z;
			const auto new_min=DirectX::XMVectorMin(src_min_vec,dst_min_vec);
			const auto new_max=DirectX::XMVectorMax(src_max_vec,dst_max_vec);
			const CSInt3 new_size=new_max-new_min+one_vec;
			const auto new_volume=new_size.x*new_size.y*new_size.z;
			if(new_volume==src_volume+dst_volume)
			{
				setMin(new_min);
				setMax(new_max);
				return true;
			}
			else
				return false;
		}
		Boolean contains(DirectX::FXMVECTOR blockPositionVec)const
		{
			assert(isValidate());
			return (getMin()<=blockPositionVec)&&(getMax()>=blockPositionVec);
		}
		Boolean contains(const CRange3I & range)const
		{
			assert(isValidate()&&range.isValidate());
			return (getMin()<=range.getMin())&&(getMax()>=range.getMax());
		}
		static Void createIntersection(const CRange3I & r0,const CRange3I & r1,OUT CRange3I & range)
		{
			assert(r0.isValidate()&&r1.isValidate());
			range.setMin(DirectX::XMVectorMax(r0.getMin(),r1.getMin()));
			range.setMax(DirectX::XMVectorMin(r0.getMax(),r1.getMax()));
		}
		template<class srcContainerT>
		static Void createRanges(const srcContainerT & positions,OUT TList<CRange3I*> & ranges)
		{
			for(auto iter_pos=positions.begin(),end_pos=positions.end();end_pos!=iter_pos;++iter_pos)
			{
				auto const & position=*iter_pos;
				CRange3I merge_range(position,position);
				Boolean need_merge_range=false;
				do
				{
					for(auto iter_range=ranges.begin(),end_range=ranges.end();end_range!=iter_range;++iter_range)
					{
						auto range=*iter_range;
						if(range->merge(merge_range))
						{
							memcpy(&merge_range,&range,sizeof(CRange3I));
							DEVILX_DELETE range;
							ranges.erase(iter_range);
							need_merge_range=true;
							break;
						}
					}
				}
				while(need_merge_range);
				ranges.insert(ranges.end(),DEVILX_NEW CRange3I(merge_range));
			}
		}
		static Void eraseRange(const CRange3I & srcRange,const CRange3I & erasedRange,OUT TList<CRange3I*> & newRanges)
		{
			assert(srcRange.contains(erasedRange));
			//split by min x
			if(erasedRange.getMin().x>srcRange.getMin().x)
			{
				newRanges.push_back(DEVILX_NEW CRange3I(srcRange.getMin(),CSInt3(erasedRange.getMin().x-1,srcRange.getMax().y,srcRange.getMax().z)));
			}
			//split by max x
			if(erasedRange.getMax().x<srcRange.getMax().x)
			{
				newRanges.push_back(DEVILX_NEW CRange3I(CSInt3(erasedRange.getMax().x+1,srcRange.getMin().y,srcRange.getMin().z),srcRange.getMax()));
			}
			//split by min y
			if(erasedRange.getMin().y>srcRange.getMin().y)
			{
				newRanges.push_back(DEVILX_NEW CRange3I(CSInt3(erasedRange.getMin().x,srcRange.getMin().y,srcRange.getMin().z),CSInt3(erasedRange.getMax().x,erasedRange.getMin().y-1,srcRange.getMax().z)));
			}
			//split by max y
			if(erasedRange.getMax().y<srcRange.getMax().y)
			{
				newRanges.push_back(DEVILX_NEW CRange3I(CSInt3(erasedRange.getMin().x,erasedRange.getMax().y+1,srcRange.getMin().z),CSInt3(erasedRange.getMax().x,srcRange.getMax().y,srcRange.getMax().z)));
			}
			//split by min z
			if(erasedRange.getMin().z>srcRange.getMin().z)
			{
				newRanges.push_back(DEVILX_NEW CRange3I(CSInt3(erasedRange.getMin().x,erasedRange.getMin().y,srcRange.getMin().z),CSInt3(erasedRange.getMax().x,erasedRange.getMax().y,erasedRange.getMin().z-1)));
			}
			//split by max z
			if(erasedRange.getMax().z<srcRange.getMax().z)
			{
				newRanges.push_back(DEVILX_NEW CRange3I(CSInt3(erasedRange.getMin().x,erasedRange.getMin().y,erasedRange.getMax().z+1),CSInt3(erasedRange.getMax().x,erasedRange.getMax().y,srcRange.getMax().z)));
			}
		}
	};
}
