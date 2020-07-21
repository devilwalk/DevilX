#pragma once
namespace NSDevilX
{
	template<typename TPointer>
	class TPointerProxy
	{
	protected:
		TPointer * mInternal;
	public:
		TPointerProxy(TPointer * ptr)
			:mInternal(ptr)
		{
		}
		~TPointerProxy()
		{
		}
		TPointer * operator->()const
		{
			return mInternal;
		}
		TPointer & operator*()const
		{
			return *mInternal;
		}
	};
	template<typename TPointer>
	class TSharedPointerObject
		:public std::shared_ptr<TPointerProxy<TPointer> >
	{
	public:
		using std::shared_ptr<TPointerProxy<TPointer> >::shared_ptr;
		TSharedPointerObject(TPointer * ptr)
			:std::shared_ptr<TPointerProxy<TPointer> >(new TPointerProxy<TPointer>(ptr))
		{

		}
		~TSharedPointerObject()
		{

		}
	};
}