#pragma once
namespace NSDevilX
{
	class CStringUtility
	{
	public:
		static Void split(ConstCharPtr text,ConstCharPtr splitKey,OUT std::vector<std::string> & ret)
		{
			std::string copy=text;
			while(std::string::npos!=copy.find(splitKey))
			{
				ret.push_back(copy.substr(0,copy.find_first_of(splitKey)));
				copy=copy.substr(copy.find_first_of(splitKey)+1);
			}
			ret.push_back(copy);
		}
		template<typename T>
		static ConstCharPtr toString(T t)
		{
			std::string ret;
			std::stringstream ss;
			ss<<t;
			ss>>ret;
			return ret.c_str();
		}
		template<typename T>
		static T toValue(ConstCharPtr text)
		{
			T ret;
			std::stringstream ss;
			ss<<text;
			ss>>ret;
			return ret;
		}
		static ConstCharPtr toString(const CFloat4 & value)
		{
			std::string ret;
			ret+=toString(value.x);
			ret+=",";
			ret+=toString(value.y);
			ret+=",";
			ret+=toString(value.z);
			ret+=",";
			ret+=toString(value.w);
			return ret.c_str();
		}
		static ConstCharPtr toString(const CFloat3 & value)
		{
			std::string ret;
			ret+=toString(value.x);
			ret+=",";
			ret+=toString(value.y);
			ret+=",";
			ret+=toString(value.z);
			return ret.c_str();
		}
		static ConstCharPtr toString(const CFloat2 & value)
		{
			std::string ret;
			ret+=toString(value.x);
			ret+=",";
			ret+=toString(value.y);
			return ret.c_str();
		}
		static Void toValue(ConstCharPtr str,CFloat4 & ret)
		{
			std::vector<std::string> values;
			split(str,",",values);
			ret.x=toValue<Float>(values[0].c_str());
			ret.y=toValue<Float>(values[1].c_str());
			ret.z=toValue<Float>(values[2].c_str());
			ret.w=toValue<Float>(values[3].c_str());
		}
		static Void toValue(ConstCharPtr str,CFloat3 & ret)
		{
			std::vector<std::string> values;
			split(str,",",values);
			ret.x=toValue<Float>(values[0].c_str());
			ret.y=toValue<Float>(values[1].c_str());
			ret.z=toValue<Float>(values[2].c_str());
		}
		static Void toValue(ConstCharPtr str,CFloat2 & ret)
		{
			std::vector<std::string> values;
			split(str,",",values);
			ret.x=toValue<Float>(values[0].c_str());
			ret.y=toValue<Float>(values[1].c_str());
		}
		static CFloat4 toFloat4(ConstCharPtr str)
		{
			CFloat4 ret;
			toValue(str,ret);
			return ret;
		}
		static CFloat3 toFloat3(ConstCharPtr str)
		{
			CFloat3 ret;
			toValue(str,ret);
			return ret;
		}
		static CFloat2 toFloat2(ConstCharPtr str)
		{
			CFloat2 ret;
			toValue(str,ret);
			return ret;
		}
	};
}