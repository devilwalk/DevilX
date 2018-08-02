#pragma once
#include "MemoryAllocatorObjectTemplate.h"
namespace NSDevilX
{
	namespace NSCore
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
#define TDevilXVector(TValue) NSDevilX::TVector<TValue,DevilXAllocator<TValue> >
#define TDevilXList(TValue) NSDevilX::TList<TValue,DevilXAllocator<TValue> >
#define TDevilXSet(TValue,TSortFunc) NSDevilX::TSet<TValue,TSortFunc,DevilXAllocator<TValue> >
#define TDevilXMap(TKey,TValue,TSortFunc) NSDevilX::TMap<TKey,TValue,TSortFunc,DevilXAllocator<std::pair<const TKey,TValue> > >
	}
}
