#pragma once
namespace NSDevilX
{
	typedef std::basic_string<Char,std::char_traits<Char>,DevilXAllocator<Char> > String;
	typedef std::basic_string<WChar,std::char_traits<WChar>,DevilXAllocator<WChar> > WString;
	typedef std::basic_stringstream<Char,std::char_traits<Char>,DevilXAllocator<Char> > StringStream;
	typedef std::basic_stringstream<WChar,std::char_traits<WChar>,DevilXAllocator<WChar> > WStringStream;
#ifdef UNICODE
	typedef WString TString;
	typedef WStringStream TStringStream;
#else
	typedef String TString;
	typedef StringStream TStringStream;
#endif
#define TVector(TValue) NSDevilX::TVector<TValue,DevilXAllocator<TValue> >
#define TList(TValue) NSDevilX::TList<TValue,DevilXAllocator<TValue> >
#define TSet(TValue) NSDevilX::TSet<TValue,std::less<TValue>,DevilXAllocator<TValue> >
#define TMap(TKey,TValue) NSDevilX::TMap<TKey,TValue,std::less<TKey>,DevilXAllocator<std::pair<TKey,TValue> > >
#define toString(x) CStringUtility::toString<decltype(x),DevilXAllocator<Char> >(x)
}