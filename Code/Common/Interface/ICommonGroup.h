#pragma once
namespace NSDevilX
{
	template<typename TValue,class TIterator>
	class TIGroup
	{
	protected:
		virtual ~TIGroup()
		{
		}
	public:
		virtual TIterator begin()const=0;
		virtual TIterator end()const=0;
	};
}