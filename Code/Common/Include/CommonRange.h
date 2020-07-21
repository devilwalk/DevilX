#pragma once
#include "CommonVector.h"
namespace NSDevilX
{
	class CRangeI
	{
	public:
		typedef Int32 DATA_TYPE;
	protected:
		Int32 mMin;
		Int32 mMax;
	public:
		CRangeI()
			:mMin(1)
			,mMax(0)
		{}
		CRangeI(Int32 minPosition,Int32 maxPosition)
			:mMin(minPosition)
			,mMax(maxPosition)
		{}
		~CRangeI()
		{}
		Boolean isValidate()const
		{
			return getMax()>=getMin();
		}
		Void setMin(Int32 value)
		{
			mMin=value;
		}
		Int32 getMin()const
		{
			return mMin;
		}
		Void setMax(Int32 value)
		{
			mMax=value;
		}
		Int32 getMax()const
		{
			return mMax;
		}
		Boolean merge(const CRangeI & range)
		{
			assert(isValidate()&&range.isValidate());
			if((getMin()-1>range.getMax())||(range.getMin()-1>getMax()))
				return false;
			else
			{
				setMin(std::min<UInt32>(getMin(),range.getMin()));
				setMax(std::max<UInt32>(getMax(),range.getMax()));
				return true;
			}
		}
		Boolean mergeTest(const CRangeI & range)
		{
			assert(isValidate()&&range.isValidate());
			if((getMin()-1>range.getMax())||(range.getMin()-1>getMax()))
				return false;
			else
			{
				return true;
			}
		}
		UInt32 length()const
		{
			return static_cast<UInt32>(getMax()-getMin()+1);
		}
	};
	class COrderedRangesI
		:public TList<CRangeI>
	{
	public:
		using TList<CRangeI>::TList;
		Void addRange(const CRangeI & range)
		{
			if(range.isValidate())
			{
				if((empty())||(back().getMax()<range.getMin()-1))
					push_back(range);
				else if(front().getMin()-1>range.getMax())
					push_front(range);
				else
				{
					//缩小范围
					iterator iter_begin=begin();
					iterator iter_end=end();
					for(auto iter=begin();end()!=iter;++iter)
					{
						auto & test=*iter;
						if(test.getMin()<=range.getMin())
						{
							iter_begin=iter;
						}
						if(test.getMax()>=range.getMax())
						{
							iter_end=++iter;
							break;
						}
					}
					//在范围内尝试合并
					Boolean merged=false;
					for(auto iter=iter_begin;iter!=iter_end;++iter)
					{
						auto & test=*iter;
						if(test.merge(range))
						{
							auto next_iter=++iter;
							--iter;
							COrderedRangesI next_ranges(next_iter,iter_end);
							next_ranges.addRange(test);
							erase(iter,iter_end);
							insert(iter_end,next_ranges.begin(),next_ranges.end());
							merged=true;
							break;
						}
					}
					//不能合并说明范围只有两个
					if(!merged)
					{
						insert(iter_end,range);
					}
				}
			}
		}
	};
	class CRange3I
	{
	public:
		enum EMergeResult
		{
			EMergeResult_Success,
			EMergeResult_NearBy,
			EMergeResult_Fail
		};
		typedef CInt3 DATA_TYPE;
	protected:
		CInt3 mMin;
		CInt3 mMax;
	public:
		CRange3I()
			:mMin(1,1,1)
			,mMax(0,0,0)
		{}
		CRange3I(const CInt3 & minPosition,const CInt3 & maxPosition)
			:mMin(minPosition)
			,mMax(maxPosition)
		{
		}
		~CRange3I()
		{}
		Boolean isValidate()const
		{
			return CMath::all(CMath::greaterEqual(getMax(),getMin()));
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
		Void setMin(const CInt3 & vec)
		{
			mMin=vec;
		}
		const CInt3 & getMin()const
		{
			return mMin;
		}
		Void setMax(const CInt3 & vec)
		{
			mMax=vec;
		}
		const CInt3 & getMax()const
		{
			return mMax;
		}
		EMergeResult merge(const CRange3I & range,OUT CRange3I * mergedRange)const
		{
			assert(isValidate()&&range.isValidate());
			const auto& src_min_vec=getMin();
			const auto& src_max_vec=getMax();
			const auto& dst_min_vec=range.getMin();
			const auto& dst_max_vec=range.getMax();
			const auto& one_vec=CMath::sInt3_One;
			const auto src_size=src_max_vec-src_min_vec+one_vec;
			const auto src_volume=src_size.x*src_size.y*src_size.z;
			const auto dst_size=dst_max_vec-dst_min_vec+one_vec;
			const auto dst_volume=dst_size.x*dst_size.y*dst_size.z;
			const auto new_min=CMath::min(src_min_vec,dst_min_vec);
			const auto new_max=CMath::max(src_max_vec,dst_max_vec);
			const auto new_size=new_max-new_min+one_vec;
			const auto new_volume=new_size.x*new_size.y*new_size.z;
			if(new_volume<=src_volume+dst_volume)
			{
				if(mergedRange)
				{
					mergedRange->setMin(new_min);
					mergedRange->setMax(new_max);
				}
				return EMergeResult_Success;
			}
			else
			{
				auto delta_size=new_size-(src_size+dst_size);
				if((delta_size.x==0&&delta_size.y==0)||(delta_size.x==0&&delta_size.z==0)||(delta_size.z==0&&delta_size.y==0))
					return EMergeResult_NearBy;
				else
					return EMergeResult_Fail;
			}
		}
		EMergeResult merge(const CRange3I & range)
		{
			return merge(range,this);
		}
		Boolean contains(const CInt3 & position)const
		{
			assert(isValidate());
			return CMath::all(CMath::lessEqual(getMin(),position))&&CMath::all(CMath::greaterEqual(getMax(),position));
		}
		Boolean contains(const CRange3I & range)const
		{
			assert(isValidate()&&range.isValidate());
			return CMath::all(CMath::lessEqual(getMin(),range.getMin()))&&CMath::all(CMath::greaterEqual(getMax(),range.getMax()));
		}
		static Void createIntersection(const CRange3I & r0,const CRange3I & r1,OUT CRange3I & range)
		{
			assert(r0.isValidate()&&r1.isValidate());
			range.setMin(CMath::max(r0.getMin(),r1.getMin()));
			range.setMax(CMath::min(r0.getMax(),r1.getMax()));
		}
		template<class srcContainerT,class dstContainerT>
		static Void createRanges(const srcContainerT & positions,OUT dstContainerT & ranges)
		{
			TResourcePtrList<CRange3I> temp_ranges;
			for(auto iter_pos=positions.begin(),end_pos=positions.end();end_pos!=iter_pos;++iter_pos)
			{
				auto const & position=*iter_pos;
				CRange3I merge_range(position,position);
				Boolean need_merge_range=false;
				do
				{
					need_merge_range=false;
					for(auto iter_range=temp_ranges.begin(),end_range=temp_ranges.end();end_range!=iter_range;++iter_range)
					{
						auto range=*iter_range;
						if(EMergeResult_Success==range->merge(merge_range))
						{
							merge_range.setMax(range->getMax());
							merge_range.setMin(range->getMin());
							delete range;
							temp_ranges.erase(iter_range);
							need_merge_range=true;
							break;
						}
					}
				}
				while(need_merge_range);
				temp_ranges.insert(temp_ranges.end(),new CRange3I(merge_range));
			}
			for(auto range:temp_ranges)
			{
				ranges.push_back(*range);
			}
		}
		static Void eraseRange(const CRange3I & srcRange,const CRange3I & erasedRange,OUT TList<CRange3I*> & newRanges)
		{
			assert(srcRange.contains(erasedRange));
			//split by min x
			if(erasedRange.getMin().x>srcRange.getMin().x)
			{
				newRanges.push_back(new CRange3I(srcRange.getMin(),CInt3(erasedRange.getMin().x-1,srcRange.getMax().y,srcRange.getMax().z)));
			}
			//split by max x
			if(erasedRange.getMax().x<srcRange.getMax().x)
			{
				newRanges.push_back(new CRange3I(CInt3(erasedRange.getMax().x+1,srcRange.getMin().y,srcRange.getMin().z),srcRange.getMax()));
			}
			//split by min y
			if(erasedRange.getMin().y>srcRange.getMin().y)
			{
				newRanges.push_back(new CRange3I(CInt3(erasedRange.getMin().x,srcRange.getMin().y,srcRange.getMin().z),CInt3(erasedRange.getMax().x,erasedRange.getMin().y-1,srcRange.getMax().z)));
			}
			//split by max y
			if(erasedRange.getMax().y<srcRange.getMax().y)
			{
				newRanges.push_back(new CRange3I(CInt3(erasedRange.getMin().x,erasedRange.getMax().y+1,srcRange.getMin().z),CInt3(erasedRange.getMax().x,srcRange.getMax().y,srcRange.getMax().z)));
			}
			//split by min z
			if(erasedRange.getMin().z>srcRange.getMin().z)
			{
				newRanges.push_back(new CRange3I(CInt3(erasedRange.getMin().x,erasedRange.getMin().y,srcRange.getMin().z),CInt3(erasedRange.getMax().x,erasedRange.getMax().y,erasedRange.getMin().z-1)));
			}
			//split by max z
			if(erasedRange.getMax().z<srcRange.getMax().z)
			{
				newRanges.push_back(new CRange3I(CInt3(erasedRange.getMin().x,erasedRange.getMin().y,erasedRange.getMax().z+1),CInt3(erasedRange.getMax().x,erasedRange.getMax().y,srcRange.getMax().z)));
			}
		}
	};
}
