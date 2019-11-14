#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		struct SGLStateChange
		{
			virtual Void apply()=0;
		};
#define SGLState1(func,argType0) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
S##func(argType0 v0):mV0(v0){} \
virtual Void apply() override {func(mV0);}}
#define SGLState2(func,argType0,argType1) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
argType1 mV1; \
S##func(argType0 v0,argType1 v1):mV0(v0),mV1(v1){} \
virtual Void apply() override {func(mV0,mV1);}}
#define SGLState3(func,argType0,argType1,argType2) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
argType1 mV1; \
argType2 mV2; \
S##func(argType0 v0,argType1 v1,argType2 v2):mV0(v0),mV1(v1),mV2(v2){} \
virtual Void apply() override {func(mV0,mV1,mV2);}}
#define SGLState4(func,argType0,argType1,argType2,argType3) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
argType1 mV1; \
argType2 mV2; \
argType3 mV3; \
S##func(argType0 v0,argType1 v1,argType2 v2,argType3 v3):mV0(v0),mV1(v1),mV2(v2),mV3(v3){} \
virtual Void apply() override {func(mV0,mV1,mV2,mV3);}}
#define SGLState5(func,argType0,argType1,argType2,argType3,argType4) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
argType1 mV1; \
argType2 mV2; \
argType3 mV3; \
argType4 mV4; \
S##func(argType0 v0,argType1 v1,argType2 v2,argType3 v3,argType4 v4):mV0(v0),mV1(v1),mV2(v2),mV3(v3),mV4(v4){} \
virtual Void apply() override {func(mV0,mV1,mV2,mV3,mV4);}}

#define SGLState1Generate(func) SGLState1(##func,GLenum)
#define SGLState1iGenerate(func) SGLState2(##func,GLenum,GLuint)
#define SGLStatei1Generate(func) SGLState2(##func,GLuint,GLenum)
#define SGLState2Generate(func) SGLState2(##func,GLenum,GLenum)
#define SGLStatei2Generate(func) SGLState3(##func,GLuint,GLenum,GLenum)
#define SGLState3Generate(func) SGLState3(##func,GLenum,GLenum,GLenum)
#define SGLStatei3Generate(func) SGLState4(##func,GLuint,GLenum,GLenum,GLenum)
#define SGLState4Generate(func) SGLState4(##func,GLenum,GLenum,GLenum,GLenum)
#define SGLStatei4Generate(func) SGLState5(##func,GLuint,GLenum,GLenum,GLenum,GLenum)

#define SGLPointerState1(func,argType0) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
S##func(argType0 v0):mV0(v0){} \
~S##func(){delete mV0;} \
virtual Void apply() override {func(mV0);}}
#define SGLPointerState2(func,argType0,argType1) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
argType1 mV1; \
S##func(argType0 v0,argType1 v1):mV0(v0),mV1(v1){} \
~S##func(){delete mV1;} \
virtual Void apply() override {func(mV0,mV1);}}
#define SGLPointerState3(func,argType0,argType1,argType2) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
argType1 mV1; \
argType2 mV2; \
S##func(argType0 v0,argType1 v1,argType2 v2):mV0(v0),mV1(v1),mV2(v2){} \
~S##func(){delete mV2;} \
virtual Void apply() override {func(mV0,mV1,mV2);}}
#define SGLPointerState4(func,argType0,argType1,argType2,argType3) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
argType1 mV1; \
argType2 mV2; \
argType3 mV3; \
S##func(argType0 v0,argType1 v1,argType2 v2,argType3 v3):mV0(v0),mV1(v1),mV2(v2),mV3(v3){} \
~S##func(){delete mV3;} \
virtual Void apply() override {func(mV0,mV1,mV2,mV3);}}
#define SGLPointerState5(func,argType0,argType1,argType2,argType3,argType4) \
struct S##func:public SGLStateChange{ \
argType0 mV0; \
argType1 mV1; \
argType2 mV2; \
argType3 mV3; \
argType4 mV4; \
S##func(argType0 v0,argType1 v1,argType2 v2,argType3 v3,argType4 v4):mV0(v0),mV1(v1),mV2(v2),mV3(v3),mV4(v4){} \
~S##func(){delete mV4;} \
virtual Void apply() override {func(mV0,mV1,mV2,mV3,mV4);}}

		SGLState1Generate(glEnable);
		SGLState1Generate(glDisable);
		SGLState1Generate(glBlendEquation);
		SGLState1Generate(glLogicOp);
		SGLState1Generate(glDepthFunc);
		SGLState1Generate(glCullFace);
		SGLState1Generate(glFrontFace);
		SGLState1(glDepthMask,GLboolean);
		SGLState1(glStencilMask,GLuint);
		SGLState1(glMinSampleShading,GLfloat);
		SGLState1iGenerate(glEnablei);
		SGLState1iGenerate(glDisablei);
		SGLState2Generate(glBlendFunc);
		SGLState2Generate(glBlendEquationi);
		SGLState2Generate(glBlendEquationSeparate);
		SGLState2Generate(glPolygonMode);
		SGLState2(glPolygonOffset,GLfloat,GLfloat);
		SGLStatei2Generate(glBlendEquationSeparatei);
		SGLStatei2Generate(glBlendFunci);
		SGLState3Generate(glStencilOp);
		SGLState3(glStencilFunc,GLenum,GLint,GLuint);
		SGLState3(glPolygonOffsetClamp,GLfloat,GLfloat,GLfloat);
		SGLState3(glTexParameteri,GLenum,GLenum,GLint);
		SGLState3(glTexParameterf,GLenum,GLenum,GLfloat);
		SGLState3(glTexParameteriv,GLenum,GLenum,const GLint*);
		SGLPointerState3(glTexParameterfv,GLenum,GLenum,GLfloat*);
		SGLState4Generate(glBlendFuncSeparate);
		SGLState4Generate(glStencilOpSeparate);
		SGLState4(glStencilFuncSeparate,GLenum,GLenum,GLint,GLuint);
		SGLState4(glColorMask,GLboolean,GLboolean,GLboolean,GLboolean);
		SGLStatei4Generate(glBlendFuncSeparatei);
		SGLState5(glColorMaski,GLuint,GLboolean,GLboolean,GLboolean,GLboolean);

		class CGLStateImp
			:public IBlendState
			,public IDepthStencilState
			,public IRasterizerState
			,public ISamplerState
		{
		public:
			friend class CGLDeviceImp;
		protected:
			TResourcePtrVector<SGLStateChange> mStateChanges;
		public:
			CGLStateImp();
			virtual ~CGLStateImp();
		};
	}
}