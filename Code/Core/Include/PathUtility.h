#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class CPathUtility
		{
		public:
			template<typename TChar>
			static TVector<TChar> getParent(const TVector<TChar> & path)
			{
				TVector<SizeT> indices;
				Boolean skip=true;
				for(SizeT i=path.size()-1;i>=0;--i)
				{
					auto & c=path[i];
					if(!skip)
					{
						indices.push_back(i);
					}
					if(c=="\\"||c=="/")
						skip=false;
				}
				TVector<TChar> ret;
				ret.reserve(indices.size())
				for(SizeT i=indices.size()-1;i>=0;--i)
				{
					ret.push_back(path[indices[i]]);
				}
				return ret;
			}
			static String getParent(const String & path)
			{
				auto && ret=getParent(TVector<Char>(path.begin(),path.end()));
				return String(ret.begin(),ret.end());
			}
			static WString getParent(const WString & path)
			{
				auto && ret=getParent(TVector<WChar>(path.begin(),path.end()));
				return WString(ret.begin(),ret.end());
			}
			static CUTF8String getParent(const CUTF8String & path)
			{
				return CUTF8String(getParent<CUTF8Char>(path));
			}
			static CUTF16String getParent(const CUTF16String & path)
			{
				return CUTF16String(getParent<CUTF16Char>(path));
			}
		};
	}
}