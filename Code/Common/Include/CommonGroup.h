#pragma once
#include "ICommonGroup.h"
namespace NSDevilX
{
	template<class TContainer>
	class TGroup
		:public TIGroup<typename TContainer::value_type,typename TContainer::iterator>
		,public TContainer
	{
	public:
		TGroup()
		{

		}
		virtual ~TGroup()
		{

		}
		virtual typename TContainer::iterator begin()const override
		{
			return TIGroup<typename TContainer::value_type,typename TContainer::iterator>::begin();
		}
		virtual typename TContainer::iterator end()const override
		{
			return TIGroup<typename TContainer::value_type,typename TContainer::iterator>::end();
		}
	};

	template<class TContainer>
	class TOrderedGroup
		:public TGroup<TContainer>
	{
	public:
		TOrderedGroup()
		{

		}
		virtual ~TOrderedGroup()
		{

		}
	};
}