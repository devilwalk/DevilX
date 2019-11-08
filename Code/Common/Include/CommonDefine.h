#pragma once
#if (!defined(DEVILX_DEBUG))&&(defined(DEBUG)||defined(_DEBUG))
#define DEVILX_DEBUG 1
#endif
#ifndef OUT
#define OUT
#endif
#define DEVILX_SAFE_RELEASE(x) {x->release();x=nullptr;}
#define DEVILX_COM_SAFE_RELEASE(x) {static_cast<IUnknown*>(x)->Release();x=nullptr;}
#define DEVILX_SAFE_DELETE(x) delete(x);x=0;
#define DEVILX_BYTE_ORDER_LITTLE_ENDIAN 0
#define DEVILX_BYTE_ORDER_BIG_ENDIAN 1
#if defined(_M_IX86)||defined(_M_X64)
#define DEVILX_BYTE_ORDER DEVILX_BYTE_ORDER_LITTLE_ENDIAN
#endif

#define DEVILX_R_CLASS_MEMBER(type,name) public: \
type get##name()const{return m##name;} \
protected: \
type m##name
#define DEVILX_R_CLASS_MEMBER_REF(type,name) public: \
const type & get##name()const{return m##name;} \
protected: \
type m##name
