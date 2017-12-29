#include "Functions.sl"
#include "FunctionsEx.sl"
#include "cbObject.sl"
#include "cbLight.sl"
#ifndef OUTPUT_WORLD_POSITION
#define OUTPUT_WORLD_POSITION 0
#endif
#ifndef OUTPUT_WORLD_NORMAL
#define OUTPUT_WORLD_NORMAL 0
#endif
#ifndef OUTPUT_WORLD_TANGENT
#define OUTPUT_WORLD_TANGENT 0
#endif
#ifndef OUTPUT_MAIN_UV
#define OUTPUT_MAIN_UV 0
#endif
#ifndef OUTPUT_DIFFUSE
#define OUTPU_DIFFUSE 0
#endif
#ifndef USE_DIRECTION_LIGHT
#define USE_DIRECTION_LIGHT 0
#endif
#ifndef USE_POINT_LIGHT
#define USE_POINT_LIGHT 0
#endif
#ifndef USE_SPOT_LIGHT
#define USE_SPOT_LIGHT 0
#endif
#ifndef USE_CONSTANT_AMBIENT_MODEL
#define USE_CONSTANT_AMBIENT_MODEL 1
#endif
#ifndef USE_HEMISPHERE_AMBIENT_MODEL
#define USE_HEMISPHERE_AMBIENT_MODEL 0
#endif
#ifndef USE_SPHERICALHARMONICS_AMBIENT_MODEL
#define USE_SPHERICALHARMONICS_AMBIENT_MODEL 0
#endif
#define USE_AMBIENT_MODEL (USE_CONSTANT_AMBIENT_MODEL||USE_HEMISPHERE_AMBIENT_MODEL||USE_SPHERICALHARMONICS_AMBIENT_MODEL)
#ifndef USE_LAMBERT_DIFFUSE_MODEL
#define USE_LAMBERT_DIFFUSE_MODEL 0
#endif
#ifndef USE_OREN_NAYAR_DIFFUSE_MODEL
#define USE_OREN_NAYAR_DIFFUSE_MODEL 0
#endif
#ifndef USE_MINNAERT_DIFFUSE_MODEL
#define USE_MINNAERT_DIFFUSE_MODEL 0
#endif
#ifndef USE_DISNEY_DIFFUSE_MODEL
#define USE_DISNEY_DIFFUSE_MODEL 0
#endif
#define USE_DIFFUSE_MODEL (USE_LAMBERT_DIFFUSE_MODEL||USE_OREN_NAYAR_DIFFUSE_MODEL||USE_MINNAERT_DIFFUSE_MODEL||USE_DISNEY_DIFFUSE_MODEL)
#ifndef USE_PHONG_SPECULAR_MODEL
#define USE_PHONG_SPECULAR_MODEL 0
#endif 
#ifndef USE_BLINNPHONG_SPECULAR_MODEL
#define USE_BLINNPHONG_SPECULAR_MODEL 0
#endif
#ifndef USE_UE4_SPECULAR_MODEL
#define USE_UE4_SPECULAR_MODEL 0
#endif
#ifndef USE_COOK_TORRANCE_SPECULAR_MODEL
#define USE_COOK_TORRANCE_SPECULAR_MODEL 0
#endif
#define USE_SPECULAR_MODEL (USE_PHONG_SPECULAR_MODEL||USE_BLINNPHONG_SPECULAR_MODEL||USE_UE4_SPECULAR_MODEL||USE_COOK_TORRANCE_SPECULAR_MODEL)
#define USE_LIGHTING (USE_AMBIENT_MODEL||USE_DIFFUSE_MODEL||USE_SPECULAR_MODEL)
#ifndef USE_DIFFUSE_TEXTURE
#define USE_DIFFUSE_TEXTURE 0
#endif
#ifndef USE_NORMAL_TEXTURE
#define USE_NORMAL_TEXTURE 0
#endif
#ifndef USE_ALPHA_TEST
#define USE_ALPHA_TEST 0
#endif