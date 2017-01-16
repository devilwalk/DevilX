#pragma once
#include "CommonSTL.h"
#include "CommonType.h"
#include "CommonStringUtility.h"
namespace NSDevilX
{
	class CStringConverter
	{
	public:
		static const String sBlank;
		template<typename T>
		static String toString(T t)
		{
			String ret;
			StringStream ss;
			ss << t;
			ss >> ret;
			return ret;
		}
		template<typename T>
		static std::string toStdString(T t)
		{
			std::string ret;
			std::stringstream ss;
			ss<<t;
			ss>>ret;
			return ret;
		}
		static String toString(const WString & t)
		{
			String ret(t.begin(), t.end());
			return ret;
		}
		static String toString(ConstWCharPtr t)
		{
			return toString(WString(t));
		}
		static WString toWString(const String & value)
		{
			WString ret(value.begin(),value.end());
			return ret;
		}
		template<typename T>
		static T toValue(const String & str)
		{
			T ret;
			StringStream ss;
			ss << str;
			ss >> ret;
			return ret;
		}
		static String toString(const CFloat4 & value)
		{
			String ret;
			ret+=toString(value.x)+",";
			ret+=toString(value.y)+",";
			ret+=toString(value.z)+",";
			ret+=toString(value.w);
			return ret;
		}
		static String toString(const CFloat3 & value)
		{
			String ret;
			ret+=toString(value.x)+",";
			ret+=toString(value.y)+",";
			ret+=toString(value.z);
			return ret;
		}
		static String toString(const CFloat2 & value)
		{
			String ret;
			ret+=toString(value.x)+",";
			ret+=toString(value.y);
			return ret;
		}
		static Void toValue(const String & str,CFloat4 & ret)
		{
			TVector<String> values;
			CStringUtility::split(str,",",values);
			ret.x=toValue<Float>(values[0]);
			ret.y=toValue<Float>(values[1]);
			ret.z=toValue<Float>(values[2]);
			ret.w=toValue<Float>(values[3]);
		}
		static Void toValue(const String & str,CFloat3 & ret)
		{
			TVector<String> values;
			CStringUtility::split(str,",",values);
			ret.x=toValue<Float>(values[0]);
			ret.y=toValue<Float>(values[1]);
			ret.z=toValue<Float>(values[2]);
		}
		static Void toValue(const String & str,CFloat2 & ret)
		{
			TVector<String> values;
			CStringUtility::split(str,",",values);
			ret.x=toValue<Float>(values[0]);
			ret.y=toValue<Float>(values[1]);
		}
		static CFloat4 toFloat4(const String & str)
		{
			TVector<String> values;
			CStringUtility::split(str,",",values);
			Float x=toValue<Float>(values[0]);
			Float y=toValue<Float>(values[1]);
			Float z=toValue<Float>(values[2]);
			Float w=toValue<Float>(values[3]);
			return CFloat4(x,y,z,w);
		}
		static CFloat3 toFloat3(const String & str)
		{
			TVector<String> values;
			CStringUtility::split(str,",",values);
			Float x=toValue<Float>(values[0]);
			Float y=toValue<Float>(values[1]);
			Float z=toValue<Float>(values[2]);
			return CFloat3(x,y,z);
		}
		static CFloat2 toFloat2(const String & str)
		{
			TVector<String> values;
			CStringUtility::split(str,",",values);
			Float x=toValue<Float>(values[0]);
			Float y=toValue<Float>(values[1]);
			return CFloat2(x,y);
		}
	};
}