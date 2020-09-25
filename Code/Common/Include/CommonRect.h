#pragma once
namespace NSDevilX
{
	template<typename TValue>
	class TRect
		:public TMemoryAllocatorObject<TRect<TValue> >
	{
	public:
		TValue mLeft;
		TValue mTop;
		TValue mRight;
		TValue mBottom;
		TRect()
			:mLeft(0)
			,mTop(0)
			,mRight(0)
			,mBottom(0)
		{ }
		TRect(TValue left,TValue top,TValue right,TValue bottom)
			:mLeft(left)
			,mTop(top)
			,mRight(right)
			,mBottom(bottom)
		{

		}
		~TRect(){ }
		TValue width()const
		{
			return mRight-mLeft;
		}
		TValue height()const
		{
			return std::abs<TValue>(mBottom-mTop);
		}
	};
	typedef TRect<Int32> CRect;
}