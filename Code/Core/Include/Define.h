#pragma once
#if (!defined(DEVILX_DEBUG))&&(defined(DEBUG)||defined(_DEBUG))
#define DEVILX_DEBUG 1
#endif
#ifndef OUT
#define OUT
#endif
#define DEVILX_SAFE_DELETE(x) DEVILX_DELETE(x);x=0;
#define DEVILX_BYTE_ORDER_LITTLE_ENDIAN 0
#define DEVILX_BYTE_ORDER_BIG_ENDIAN 1
#if DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_WINDOWS
#define DEVILX_BYTE_ORDER DEVILX_BYTE_ORDER_LITTLE_ENDIAN
#elif DEVILX_OPERATING_SYSTEM==DEVILX_OPERATING_SYSTEM_LINUX
#endif

#define DEVILX_R_CLASS_MEMBER(type,name) public: \
type get##name()const{return m##name;} \
protected: \
type m##name
#define DEVILX_R_CLASS_MEMBER_REF(type,name) public: \
const type & get##name()const{return m##name;} \
protected: \
type m##name
