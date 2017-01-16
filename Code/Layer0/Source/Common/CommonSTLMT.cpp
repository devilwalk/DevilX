#include "Precompiler.h"
using namespace NSDevilX;
NSDevilX::CPointerQueueMT::CPointerQueueMT()
	:mInternalQueue(nullptr)
{
	mInternalQueue=new tbb::concurrent_bounded_queue<VoidPtr>;
}

NSDevilX::CPointerQueueMT::~CPointerQueueMT()
{
	delete static_cast<tbb::concurrent_bounded_queue<VoidPtr>*>(mInternalQueue);
}

Void NSDevilX::CPointerQueueMT::clear()
{
	static_cast<tbb::concurrent_bounded_queue<VoidPtr>*>(mInternalQueue)->clear();
}

Boolean NSDevilX::CPointerQueueMT::empty()
{
	return static_cast<tbb::concurrent_bounded_queue<VoidPtr>*>(mInternalQueue)->empty();
}

Void NSDevilX::CPointerQueueMT::_push(VoidPtr data)
{
	static_cast<tbb::concurrent_bounded_queue<VoidPtr>*>(mInternalQueue)->push(data);
}

VoidPtr NSDevilX::CPointerQueueMT::_pop()
{
	VoidPtr ret=nullptr;
	static_cast<tbb::concurrent_bounded_queue<VoidPtr>*>(mInternalQueue)->pop(ret);
	return ret;
}

Boolean NSDevilX::CPointerQueueMT::_tryPop(VoidPtr & data)
{
	return static_cast<tbb::concurrent_bounded_queue<VoidPtr>*>(mInternalQueue)->try_pop(data);
}

NSDevilX::CUnorderListMT::CUnorderListMT()
{
}

Void NSDevilX::CUnorderListMT::pushMT(VoidPtr value)
{
	Bool success=False;
	auto & datas=mDatas.beginRead();
	for(auto data:datas)
	{
		VoidPtr temp=nullptr;
		if(data->tryBeginRead(temp))
		{
			data->endRead();
			if(!temp)
			{
				if(data->tryBeginWrite(value))
				{
					data->endWrite();
					success=True;
					break;
				}
			}
		}
	}
	mDatas.endRead();
	if(!success)
	{
		mDatas.beginWrite().push_back(DEVILX_NEW TSharedReadData<VoidPtr>(value));
		mDatas.endWrite();
	}
}

VoidPtr NSDevilX::CUnorderListMT::tryPopMT()
{
	VoidPtr ret=nullptr;
	auto & datas=mDatas.beginRead();
	for(auto data:datas)
	{
		VoidPtr temp=nullptr;
		if(data->tryBeginRead(temp))
		{
			data->endRead();
		}
		if(temp)
		{
			if(data->tryBeginWrite(ret))
			{
				data->endWrite();
				ret=temp;
				break;
			}
		}
	}
	mDatas.endRead();
	return ret;
}

VoidPtr NSDevilX::CUnorderListMT::popMT()
{
	VoidPtr ret=nullptr;
	auto & datas=mDatas.beginRead();
	while(true)
	{
		UInt32 volidate_count=0;
		for(auto data:datas)
		{
			VoidPtr temp=nullptr;
			if(data->tryBeginRead(temp))
			{
				data->endRead();
				if(temp)
				{
					if(data->tryBeginWrite(ret))
					{
						data->endWrite();
						ret=temp;
						goto SEACH_FINISH;
					}
					else
					{
						++volidate_count;
					}
				}
			}
			else
			{
				++volidate_count;
			}
		}
		if(!volidate_count)
			break;
	}
SEACH_FINISH:
	mDatas.endRead();
	return ret;
}
