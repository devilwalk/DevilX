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
			enum EProfileCore
			{
				EProfileCore_3,
				EProfileCore_3_1,
				EProfileCore_3_2,
				EProfileCore_3_3,
				EProfileCore_4,
				EProfileCore_4_1,
				EProfileCore_4_2,
				EProfileCore_4_3,
				EProfileCore_4_4,
				EProfileCore_4_5,
				EProfileCore_4_6,
				EProfileCore_Count,
			};
			enum EProfileExt
			{
				EProfileExt_3,
				EProfileExt_3_1,
				EProfileExt_3_2,
				EProfileExt_3_3,
				EProfileExt_4,
				EProfileExt_4_1,
				EProfileExt_4_2,
				EProfileExt_4_3,
				EProfileExt_4_4,
				EProfileExt_4_5,
				EProfileExt_4_6,
				EProfileExt_Count
			};
			enum EProfileESCore
			{
				EProfileESCore_2,
				EProfileESCore_3,
				EProfileESCore_3_1,
				EProfileESCore_3_2,
				EProfileESCore_Count,
			};
			enum EProfileESExt
			{
				EProfileESExt_2,
				EProfileESExt_3,
				EProfileESExt_3_1,
				EProfileESExt_3_2,
				EProfileESExt_Count,
			};
			static EProfileCore msProfileCore;
			static EProfileESCore msProfileESCore;
		};
		template<typename T>
		struct TGLCompatible
		{
			union
			{
				T mProfileCores[CGLGlobal::EProfileCore_Count];
				T mProfileESCores[CGLGlobal::EProfileESCore_Count];
			};
			union
			{
				T mProfileExts[CGLGlobal::EProfileESCore_Count];
				T mProfileESExts[CGLGlobal::EProfileESExt_Count];
			};

			T bestProfile(CGLGlobal::EProfileCore currentProfile)const
			{
				Int32 test=currentProfile;
				while((test>=0)&&(mProfileCores[test]==T(0)))
				{
					--test;
				}
				if(test<0)
				{
					return bestProfile(*reinterpret_cast<CGLGlobal::EProfileExt*>(&currentProfile));
				}
				return mProfileCores[test];
			}
			T bestProfile(CGLGlobal::EProfileESCore currentProfile)const
			{
				Int32 test=currentProfile;
				while((test>=0)&&(mProfileESCores[test]==T(0)))
				{
					--test;
				}
				if(test<0)
				{
					return bestProfile(*reinterpret_cast<CGLGlobal::EProfileESExt*>(&currentProfile));
				}
				return mProfileESCores[test];
			}
			T bestProfile(CGLGlobal::EProfileExt currentProfile)const
			{
				Int32 test=currentProfile;
				while((test>=0)&&(mProfileExts[test]==T(0)))
				{
					--test;
				}
				if(test<0)
				{
					return T(0);
				}
				return mProfileExts[test];
			}
			T bestProfile(CGLGlobal::EProfileESExt currentProfile)const
			{
				Int32 test=currentProfile;
				while((test>=0)&&(mProfileESExts[test]==T(0)))
				{
					--test;
				}
				if(test<0)
				{
					return T(0);
				}
				return mProfileESExts[test];
			}
			Void setProfile(CGLGlobal::EProfileCore profile,T coreValue,T extValue=0)
			{
				if(CGLGlobal::msProfileCore==CGLGlobal::EProfileCore_Count)
					return;
				mProfileCores[profile]=coreValue;
				mProfileExts[profile]=extValue;
			}
			Void setProfile(CGLGlobal::EProfileESCore profile,T coreValue,T extValue=0)
			{
				if(CGLGlobal::msProfileESCore==CGLGlobal::EProfileESCore_Count)
					return;
				mProfileESCores[profile]=coreValue;
				mProfileESExts[profile]=extValue;
			}
			operator T()const
			{
				if(CGLGlobal::msProfileCore==CGLGlobal::EProfileCore_Count)
					return bestProfile(CGLGlobal::msProfileESCore);
				else
					return bestProfile(CGLGlobal::msProfileCore);
			}
		};
	}
}