#pragma once
#include "CommonUTFString.h"
namespace NSDevilX
{
	class CPathUtility
	{
	public:
		template<typename TChar,class TAllocator>
		static std::vector<TChar,TAllocator> getParent(const std::vector<TChar,TAllocator> & path)
		{
			std::vector<SizeT> indices;
			Boolean skip=true;
			for(SizeT i=path.size()-1;i>=0;--i)
			{
				auto & c=path[i];
				if(!skip)
				{
					indices.push_back(i);
				}
				if(c=='\\'||c=='/')
					skip=false;
			}
			std::vector<TChar,TAllocator> ret;
			ret.reserve(indices.size());
			for(SizeT i=indices.size()-1;i>=0;--i)
			{
				ret.push_back(path[indices[i]]);
			}
			return ret;
		}
		template<class TAllocator>
		static std::basic_string<Char,std::char_traits<Char>,TAllocator> getParent(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & path)
		{
			auto && ret=getParent(std::vector<Char,TAllocator>(path.begin(),path.end()));
			return std::basic_string<Char,std::char_traits<Char>,TAllocator>(ret.begin(),ret.end());
		}
		template<class TAllocator>
		static std::basic_string<WChar,std::char_traits<WChar>,TAllocator> getParent(const std::basic_string<WChar,std::char_traits<WChar>,TAllocator> & path)
		{
			auto && ret=getParent(std::vector<WChar,TAllocator>(path.begin(),path.end()));
			return std::basic_string<WChar,std::char_traits<WChar>,TAllocator>(ret.begin(),ret.end());
		}
	};
}