#pragma once
#include "CommonUTFString.h"
namespace NSDevilX
{
	class CPathUtility
	{
	public:
		template<class TValue>
		static auto getParent(const TValue& path)
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
			TValue ret;
			ret.resize(indices.size());
			for(SizeT i=indices.size()-1;i>=0;--i)
			{
				ret.push_back(path[indices[i]]);
			}
			return ret;
		}
	};
}