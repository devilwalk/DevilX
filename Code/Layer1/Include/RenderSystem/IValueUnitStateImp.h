#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		template<class T>
		class IRefValueUnitStateImpT
			:public IRefValueUnitStateT<T>
			,public TBaseObject<IRefValueUnitStateImpT<T> >
			,public CMessageNotifier
			,public CUserDataContainer
		{
		public:
			enum EMessage
			{
				EMessage_BeginEnableChange,
				EMessage_EndEnableChange,
				EMessage_BeginValueChange,
				EMessage_EndValueChange
			};
		protected:
			Bool mEnable;
			T * mValue;
		public:
			IRefValueUnitStateImpT()
				:mEnable(True)
				,mValue(nullptr)
			{}
			virtual ~IRefValueUnitStateImpT()
			{
				DEVILX_DELETE(mValue);
			}
			// Inherited via IColourUnitState
			virtual Void setEnable(Bool enable) override
			{
				if(enable!=mEnable)
				{
					notify(EMessage_BeginEnableChange);
					mEnable=enable;
					notify(EMessage_EndEnableChange);
				}
			}
			virtual Bool getEnable() const override
			{
				return mEnable;
			}
			virtual Void setValue(const T & value) override
			{
				if(value!=*mValue)
				{
					notify(EMessage_BeginValueChange);
					*mValue=value;
					notify(EMessage_EndValueChange);
				}
			}
			virtual const T & getValue() const override
			{
				return *mValue;
			}
		};
		template<>
		class IRefValueUnitStateImpT<CColour>
			:public IRefValueUnitStateT<CColour>
			,public TBaseObject<IRefValueUnitStateImpT<CColour> >
			,public CMessageNotifier
			,public CUserDataContainer
		{
		public:
			enum EMessage
			{
				EMessage_BeginEnableChange,
				EMessage_EndEnableChange,
				EMessage_BeginValueChange,
				EMessage_EndValueChange
			};
		protected:
			Bool mEnable;
			CColour * mValue;
		public:
			IRefValueUnitStateImpT(CColour::EType type=CColour::EType_RGBA)
				:mEnable(True)
				,mValue(nullptr)
			{
				switch(type)
				{
				case CColour::EType_Alpha:
					mValue=DEVILX_NEW CFloatAlpha(0.0f);
					break;
				case CColour::EType_RGB:
					mValue=DEVILX_NEW CFloatRGB(CFloatRGB::sWhite);
					break;
				case CColour::EType_RGBA:
					mValue=DEVILX_NEW CFloatRGBA(CFloatRGBA::sWhite);
					break;
				case CColour::EType_HSV:
					mValue=DEVILX_NEW CFloatHSV();
					break;
				}
			}
			virtual ~IRefValueUnitStateImpT()
			{
				DEVILX_DELETE(mValue);
			}
			// Inherited via IColourUnitState
			virtual Void setEnable(Bool enable) override
			{
				if(enable!=mEnable)
				{
					notify(EMessage_BeginEnableChange);
					mEnable=enable;
					notify(EMessage_EndEnableChange);
				}
			}
			virtual Bool getEnable() const override
			{
				return mEnable;
			}
			virtual Void setValue(const CColour & value) override
			{
				if(value!=*mValue)
				{
					notify(EMessage_BeginValueChange);
					*mValue=value;
					notify(EMessage_EndValueChange);
				}
			}
			virtual const CColour & getValue() const override
			{
				return *mValue;
			}
		};
		typedef IRefValueUnitStateImpT<CColour> IColourUnitStateImp;
		template<typename T>
		class IValueUnitStateTImp
			:public IValueUnitStateT<T>
			,public TBaseObject<IValueUnitStateTImp<T> >
			,public CMessageNotifier
			,public CUserDataContainer
		{
		public:
			enum EMessage
			{
				EMessage_BeginEnableChange,
				EMessage_EndEnableChange,
				EMessage_BeginValueChange,
				EMessage_EndValueChange
			};
		protected:
			Bool mEnable;
			T mValue;
		public:
			IValueUnitStateTImp(T initValue=static_cast<T>(0))
				:mEnable(True)
				,mValue(initValue)
			{}
			virtual ~IValueUnitStateTImp()
			{
			}
			// Inherited via IColourUnitState
			virtual Void setEnable(Bool enable) override
			{
				if(enable!=mEnable)
				{
					notify(EMessage_BeginEnableChange);
					mEnable=enable;
					notify(EMessage_EndEnableChange);
				}
			}
			virtual Bool getEnable() const override
			{
				return mEnable;
			}
			virtual Void setValue(T value) override
			{
				if(value!=mValue)
				{
					notify(EMessage_BeginValueChange);
					mValue=value;
					notify(EMessage_EndValueChange);
				}
			}
			virtual T getValue() const override
			{
				return mValue;
			}
		};
		typedef IValueUnitStateTImp<Float> IFloatUnitStateImp;
	}
}