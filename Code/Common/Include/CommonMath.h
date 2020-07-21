#pragma once
#include "CommonType.h"
namespace NSDevilX
{
	typedef glm::bvec2 CBoolean2;
	typedef glm::bvec3 CBoolean3;
	typedef glm::bvec4 CBoolean4;
	typedef glm::f32vec2 CFloat2;
	typedef glm::f32vec3 CFloat3;
	typedef glm::f32vec4 CFloat4;
	typedef glm::mediump_vec2 CHalf2;
	typedef glm::mediump_vec3 CHalf3;
	typedef glm::mediump_vec4 CHalf4;
	typedef glm::i32vec2 CInt2;
	typedef glm::i32vec3 CInt3;
	typedef glm::i32vec4 CInt4;
	typedef glm::u32vec2 CUInt2;
	typedef glm::u32vec3 CUInt3;
	typedef glm::u32vec4 CUInt4;
	typedef glm::mat2x2 CFloat2x2;
	typedef glm::mat2x3 CFloat2x3;
	typedef glm::mat2x4 CFloat2x4;
	typedef glm::mat3x2 CFloat3x2;
	typedef glm::mat3x3 CFloat3x3;
	typedef glm::mat3x4 CFloat3x4;
	typedef glm::mat4x2 CFloat4x2;
	typedef glm::mat4x3 CFloat4x3;
	typedef glm::mat4x4 CFloat4x4;
	typedef glm::f32quat CQuaterionF;
	typedef glm::mediump_quat CQuaterionH;

	class CMath
	{
	public:
#define DECL(type,v) \
static const C##type##2 s##type##2_##v; \
static const C##type##3 s##type##3_##v; \
static const C##type##4 s##type##4_##v
#define DECL1(type) \
DECL(type,Zero); \
DECL(type,One)
		DECL1(Float);
		DECL1(Half);
		DECL1(Int);
		DECL1(UInt);
#undef DECL1
		DECL(Boolean,True);
		DECL(Boolean,False);
#undef DECL
#define DECL(type) static const C##type s##type##_Identity
		DECL(Float3x3);
		DECL(Float4x4);
		DECL(QuaterionF);
		DECL(QuaterionH);
#undef DECL
		static const CFloat3 sUnitX;
		static const CFloat3 sUnitY;
		static const CFloat3 sUnitZ;

		template<class TVec>
		static auto greater(const TVec& vec0,const TVec& vec1)
		{
			return glm::greaterThan(vec0,vec1);
		}
		template<class TVec>
		static auto less(const TVec& vec0,const TVec& vec1)
		{
			return glm::lessThan(vec0,vec1);
		}
		template<class TVec>
		static auto equal(const TVec& vec0,const TVec& vec1)
		{
			return glm::equal(vec0,vec1);
		}
		template<class TVec>
		static auto notEqual(const TVec& vec0,const TVec& vec1)
		{
			return glm::notEqual(vec0,vec1);
		}
		template<class TVec>
		static auto greaterEqual(const TVec& vec0,const TVec& vec1)
		{
			return glm::greaterThanEqual(vec0,vec1);
		}
		template<class TVec>
		static auto lessEqual(const TVec& vec0,const TVec& vec1)
		{
			return glm::lessThanEqual(vec0,vec1);
		}
		template<class TVec>
		static auto allGreater(const TVec& vec0,const TVec& vec1)
		{
			return all(greater(vec0,vec1));
		}
		template<class TVec>
		static auto allLess(const TVec& vec0,const TVec& vec1)
		{
			return all(less(vec0,vec1));
		}
		template<class TVec>
		static auto allEqual(const TVec& vec0,const TVec& vec1)
		{
			return all(equal(vec0,vec1));
		}
		template<class TVec>
		static auto allNotEqual(const TVec& vec0,const TVec& vec1)
		{
			return all(notEqual(vec0,vec1));
		}
		template<class TVec>
		static auto allGreaterEqual(const TVec& vec0,const TVec& vec1)
		{
			return all(greaterEqual(vec0,vec1));
		}
		template<class TVec>
		static auto allLessEqual(const TVec& vec0,const TVec& vec1)
		{
			return all(lessEqual(vec0,vec1));
		}
		template<class TBoolean>
		static auto all(const TBoolean& vec)
		{
			return glm::all(vec);
		}
		template<class TBoolean>
		static auto any(const TBoolean& vec)
		{
			return glm::any(vec);
		}
		template<class TVec>
		static auto min(const TVec& vec0,const TVec& vec1)
		{
			return glm::min(vec0,vec1);
		}
		template<class TVec>
		static auto max(const TVec& vec0,const TVec& vec1)
		{
			return glm::max(vec0,vec1);
		}
		template<class TVec>
		static auto normalize(const TVec& vec)
		{
			return glm::normalize(vec);
		}
		template<class TVec>
		static auto cross(const TVec& vec0,const TVec& vec1)
		{
			return glm::cross(vec0,vec1);
		}
		template<class TVec>
		static auto dot(const TVec& vec0,const TVec& vec1)
		{
			return glm::dot(vec0,vec1);
		}
		template<typename T>
		static auto yawPitchRoll(T yaw,T pitch,T roll)
		{
			return glm::yawPitchRoll(yaw,pitch,roll);
		}
	};
}