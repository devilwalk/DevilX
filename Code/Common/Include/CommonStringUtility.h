#pragma once
namespace NSDevilX
{
	class CStringUtility
	{
	public:
		template<class TValue>
		static auto& split(const TValue& text,const TValue& splitKey,OUT TValue& ret)
		{
			auto copy=text;
			while(TValue::npos!=copy.find(splitKey))
			{
				ret.push_back(copy.substr(0,copy.find_first_of(splitKey)));
				copy=copy.substr(copy.find_first_of(splitKey)+1);
			}
			ret.push_back(copy);
			return ret;
		}
		template<typename T,class TAllocator=std::allocator<Char> >
		static std::basic_string<Char,std::char_traits<Char>,TAllocator> & toString(T t,OUT std::basic_string<Char,std::char_traits<Char>,TAllocator> & ret)
		{
			std::basic_stringstream<Char,std::char_traits<Char>,TAllocator> ss;
			ss<<t;
			ss>>ret;
			return ret;
		}
		template<typename T,class TAllocator=std::allocator<Char> >
		static std::basic_string<Char,std::char_traits<Char>,TAllocator> toString(T t)
		{
			std::basic_string<Char,std::char_traits<Char>,TAllocator> ret;
			return toString(t,ret);
		}
		template<typename T,class TAllocator=std::allocator<Char> >
		static T toValue(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & text)
		{
			T ret;
			std::basic_stringstream<Char,std::char_traits<Char>,TAllocator> ss;
			ss<<text;
			ss>>ret;
			return ret;
		}
		template<class TAllocator=std::allocator<Char> >
		static std::basic_string<Char,std::char_traits<Char>,TAllocator> toString(const CFloat4 & value)
		{
			std::basic_string<Char,std::char_traits<Char>,TAllocator> ret;
			ret+=toString(value.x);
			ret+=",";
			ret+=toString(value.y);
			ret+=",";
			ret+=toString(value.z);
			ret+=",";
			ret+=toString(value.w);
			return ret;
		}
		template<class TAllocator=std::allocator<Char> >
		static std::basic_string<Char,std::char_traits<Char>,TAllocator> toString(const CFloat3 & value)
		{
			std::basic_string<Char,std::char_traits<Char>,TAllocator> ret;
			ret+=toString(value.x);
			ret+=",";
			ret+=toString(value.y);
			ret+=",";
			ret+=toString(value.z);
			return ret;
		}
		template<class TAllocator=std::allocator<Char> >
		static std::basic_string<Char,std::char_traits<Char>,TAllocator> toString(const CFloat2 & value)
		{
			std::basic_string<Char,std::char_traits<Char>,TAllocator> ret;
			ret+=toString(value.x);
			ret+=",";
			ret+=toString(value.y);
			return ret;
		}
		template<class TAllocator=std::allocator<Char> >
		static Void toValue(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & str,OUT CFloat4 & ret)
		{
			std::vector<std::basic_string<Char,std::char_traits<Char>,TAllocator> > values;
			split(str,",",values);
			ret.x=toValue<Float>(values[0].c_str());
			ret.y=toValue<Float>(values[1].c_str());
			ret.z=toValue<Float>(values[2].c_str());
			ret.w=toValue<Float>(values[3].c_str());
		}
		template<class TAllocator=std::allocator<Char> >
		static Void toValue(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & str,CFloat3 & ret)
		{
			std::vector<std::basic_string<Char,std::char_traits<Char>,TAllocator> > values;
			split(str,",",values);
			ret.x=toValue<Float>(values[0].c_str());
			ret.y=toValue<Float>(values[1].c_str());
			ret.z=toValue<Float>(values[2].c_str());
		}
		template<class TAllocator=std::allocator<Char> >
		static Void toValue(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & str,CFloat2 & ret)
		{
			std::vector<std::basic_string<Char,std::char_traits<Char>,TAllocator> > values;
			split(str,",",values);
			ret.x=toValue<Float>(values[0].c_str());
			ret.y=toValue<Float>(values[1].c_str());
		}
		template<class TAllocator=std::allocator<Char> >
		static CFloat4 toFloat4(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & str)
		{
			CFloat4 ret;
			toValue(str,ret);
			return ret;
		}
		template<class TAllocator=std::allocator<Char> >
		static CFloat3 toFloat3(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & str)
		{
			CFloat3 ret;
			toValue(str,ret);
			return ret;
		}
		template<class TAllocator=std::allocator<Char> >
		static CFloat2 toFloat2(const std::basic_string<Char,std::char_traits<Char>,TAllocator> & str)
		{
			CFloat2 ret;
			toValue(str,ret);
			return ret;
		}
	};
}