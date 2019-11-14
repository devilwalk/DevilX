#pragma once
namespace NSDevilX
{
	namespace NSGraphicsAPI
	{
		class CGLObject
		{
			friend class CGLDeviceImp;
		protected:
			GLuint mInternal;
		public:
			CGLObject();
			virtual ~CGLObject();
		};
		class CGLGlobal
		{
		public:
			enum EProfile
			{
				EProfile_Core_GL3,
				EProfile_Core_GL3_1,
				EProfile_Core_GL3_2,
				EProfile_Core_GL3_3,
				EProfile_Core_GL4,
				EProfile_Core_GL4_1,
				EProfile_Core_GL4_2,
				EProfile_Core_GL4_3,
				EProfile_Core_GL4_4,
				EProfile_Core_GL4_5,
				EProfile_Core_GL4_6,
				EProfile_Ext_GL3,
				EProfile_Ext_GL3_1,
				EProfile_Ext_GL3_2,
				EProfile_Ext_GL3_3,
				EProfile_Ext_GL4,
				EProfile_Ext_GL4_1,
				EProfile_Ext_GL4_2,
				EProfile_Ext_GL4_3,
				EProfile_Ext_GL4_4,
				EProfile_Ext_GL4_5,
				EProfile_Ext_GL4_6,
				EProfile_Count
			};
			enum EESProfile
			{
				EESProfile_Core_GLES2,
				EESProfile_Core_GLES3,
				EESProfile_Core_GLES3_1,
				EESProfile_Core_GLES3_2,
				EESProfile_Ext_GLES2,
				EESProfile_Ext_GLES3,
				EESProfile_Ext_GLES3_1,
				EESProfile_Ext_GLES3_2,
				EESProfile_Count
			};
			static EProfile msProfile;
			static EESProfile msESProfile;
		};
		template<typename T>
		struct TGLCompatible
		{
			union
			{
				T mProfiles[CGLGlobal::EProfile_Count];
				T mESProfiles[CGLGlobal::EESProfile_Count];
			};

			T bestProfile(CGLGlobal::EProfile currentProfile)const
			{
				Int32 test=currentProfile;
				while(mProfiles[test]==T(0))
				{
					--test;
				}
				return mProfiles[test];
			}
			T bestProfile(CGLGlobal::EESProfile currentProfile)const
			{
				Int32 test=currentProfile;
				while(mESProfiles[test]==T(0))
				{
					--test;
				}
				return mESProfiles[test];
			}
			Void setProfile(CGLGlobal::EProfile profile,T v)
			{
				if(CGLGlobal::msProfile==CGLGlobal::EProfile_Count)
					return;
				mProfiles[profile]=v;
			}
			Void setProfile(CGLGlobal::EESProfile profile,T v)
			{
				if(CGLGlobal::msESProfile==CGLGlobal::EESProfile_Count)
					return;
				mESProfiles[profile]=v;
			}
			operator T()const
			{
				if(CGLGlobal::msProfile==CGLGlobal::EProfile_Count)
					return bestProfile(CGLGlobal::msESProfile);
				else
					return bestProfile(CGLGlobal::msProfile);
			}
		};
	}
}