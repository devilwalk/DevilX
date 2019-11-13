#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLStateImp
			:public IBlendState
			,public IDepthStencilState
			,public IRasterizerState
			,public ISamplerState
		{
		public:
			friend class CGLDeviceImp;
			template<typename TValue,int TNumber>
			struct TStateChangeParameter
			{
				VoidPtr mFunction;
				TValue mValue[TNumber];
				operator delctype(mValue)& ()
				{
					return mValue;
				}
			};
			template<typename TValue>
			struct TStateChangeParameter<TValue,1>
			{
				VoidPtr mFunction;
				TValue mValue;
				operator TValue& ()
				{
					return mValue;
				}
			};
		protected:
			TVector<TStateChangeParameter<GLint,1> > mStateChangeParameters_I;
			TVector<TStateChangeParameter<GLint,2> > mStateChangeParameters_II;
			TVector<TStateChangeParameter<GLint,3> > mStateChangeParameters_III;
			TVector<TStateChangeParameter<GLint,4> > mStateChangeParameters_IIII;
			TVector<TStateChangeParameter<GLint,5> > mStateChangeParameters_IIIII;
			TVector<TStateChangeParameter<GLfloat,1> > mStateChangeParameters_F;
			TVector<TStateChangeParameter<GLfloat,2> > mStateChangeParameters_FF;
			TVector<TStateChangeParameter<GLfloat,3> > mStateChangeParameters_FFF;
		public:
			CGLStateImp();
			virtual ~CGLStateImp();

			Void addState(VoidPtr func,GLint value)
			{
				TStateChangeParameter<GLint,1> v;
				v.mFunction=func;
				v.mValue=value;
				mStateChangeParameters_I.push_back(v);
			}
			Void addState(VoidPtr func,GLint value0,GLint value1)
			{
				TStateChangeParameter<GLint,2> v;
				v.mFunction=func;
				v.mValue[0]=value0;
				v.mValue[1]=value1;
				mStateChangeParameters_II.push_back(v);
			}
			Void addState(VoidPtr func,GLint value0,GLint value1,GLint value2)
			{
				TStateChangeParameter<GLint,3> v;
				v.mFunction=func;
				v.mValue[0]=value0;
				v.mValue[1]=value1;
				v.mValue[2]=value2;
				mStateChangeParameters_III.push_back(v);
			}
			Void addState(VoidPtr func,GLint value0,GLint value1,GLint value2,GLint value3)
			{
				TStateChangeParameter<GLint,4> v;
				v.mFunction=func;
				v.mValue[0]=value0;
				v.mValue[1]=value1;
				v.mValue[2]=value2;
				v.mValue[3]=value3;
				mStateChangeParameters_IIII.push_back(v);
			}
			Void addState(VoidPtr func,GLint value0,GLint value1,GLint value2,GLint value3,GLint value4)
			{
				TStateChangeParameter<GLint,5> v;
				v.mFunction=func;
				v.mValue[0]=value0;
				v.mValue[1]=value1;
				v.mValue[2]=value2;
				v.mValue[3]=value3;
				v.mValue[4]=value4;
				mStateChangeParameters_IIIII.push_back(v);
			}
			Void addState(VoidPtr func,GLfloat value)
			{
				TStateChangeParameter<GLfloat,1> v;
				v.mFunction=func;
				v.mValue=value;
				mStateChangeParameters_F.push_back(v);
			}
			Void addState(VoidPtr func,GLfloat value0,GLfloat value1)
			{
				TStateChangeParameter<GLfloat,2> v;
				v.mFunction=func;
				v.mValue[0]=value0;
				v.mValue[1]=value1;
				mStateChangeParameters_FF.push_back(v);
			}
			Void addState(VoidPtr func,GLfloat value0,GLfloat value1,GLfloat value2)
			{
				TStateChangeParameter<GLfloat,3> v;
				v.mFunction=func;
				v.mValue[0]=value0;
				v.mValue[1]=value1;
				v.mValue[2]=value2;
				mStateChangeParameters_FFF.push_back(v);
			}
		};
	}
}