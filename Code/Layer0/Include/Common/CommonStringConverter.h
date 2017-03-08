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
		static WString UTF8ToWString(const String & value)
		{
			WString ret;
			for(size_t i=0;i<value.length();)
			{
				Byte c=value[i];
				if((c&0x80))
				{
					UInt32 byte_count=0;
					for(int bit=0;bit<8;++bit)
					{
						if((c>>(8-bit-1))&0x1)
							++byte_count;
						else
							break;
					}
					assert(byte_count>=2);
					WChar wc=0;
					for(Int32 byte_index=byte_count-1;byte_index>=0;--byte_index)
					{
						Byte b=value[i+byte_index];
						if(byte_index==0)
						{
							wc|=(b&0x1f)<<((byte_count-1)*6);
						}
						else
						{
							wc|=(b&0x3f)<<((byte_count-byte_index-1)*6);
						}
					}
					ret.push_back(wc);
					i+=byte_count;
				}
				else
				{
					ret.push_back(c);
					++i;
				}
			}
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