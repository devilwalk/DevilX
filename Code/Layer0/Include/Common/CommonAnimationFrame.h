#pragma once
#include "CommonType.h"
#include "CommonVectorF.h"
#include "CommonVectorI.h"
#include "CommonMemoryAllocatorObjectTemplate.h"
#include "CommonMessageMode.h"
namespace NSDevilX
{
	class CFrameBase
		:public CMessageNotifier
	{
	public:
		enum EMessage
		{
			EMessage_BeginValueChange,
			EMessage_EndValueChange
		};
	protected:
		CFrameBase(){}
		virtual ~CFrameBase(){}
	};
	template<typename TValueType>
	class TNumberFrame
		:public TBaseObject<TNumberFrame<TValueType> >
		,public CFrameBase
	{
	protected:
		TValueType mValue;
	public:
		TNumberFrame(TValueType value)
			:mValue(value)
		{}
		virtual ~TNumberFrame()
		{}
		Void setValue(TValueType value)
		{
			if(value!=getValue())
			{
				notify(EMessage_BeginValueChange);
				mValue=value;
				notify(EMessage_EndValueChange);
			}
		}
		TValueType getValue()const
		{
			return mValue;
		}
	};
	typedef TNumberFrame<Int8> CInt8Frame;
	typedef TNumberFrame<Int16> CInt16Frame;
	typedef TNumberFrame<Int32> CInt32Frame;
	typedef TNumberFrame<Int64> CInt64Frame;
	typedef TNumberFrame<Float> CFloatFrame;
	typedef TNumberFrame<UInt8> CUInt8Frame;
	typedef TNumberFrame<UInt16> CUInt16Frame;
	typedef TNumberFrame<UInt32> CUInt32Frame;
	typedef TNumberFrame<UInt64> CUInt64Frame;
	typedef TNumberFrame<DoubleFloat> CDoubleFloatFrame;
	template<class TValueType>
	class TVectorFrame
		:public TBaseObject<TVectorFrame<TValueType> >
		,public CFrameBase
	{
	protected:
		TValueType mValue;
	public:
		TVectorFrame(const TValueType & value)
			:mValue(value)
		{}
		virtual ~TVectorFrame()
		{}
		Void setValue(const TValueType & value)
		{
			if(value!=getValue())
			{
				notify(EMessage_BeginValueChange);
				mValue=value;
				notify(EMessage_EndValueChange);
			}
		}
		const TValueType & getValue()const
		{
			return mValue;
		}
	};
	typedef TVectorFrame<CFloat2> CFloat2Frame;
	typedef TVectorFrame<CFloat3> CFloat3Frame;
	typedef TVectorFrame<CFloat4> CFloat4Frame;
	typedef TVectorFrame<CInt2> CInt2Frame;
	typedef TVectorFrame<CInt3> CInt3Frame;
	typedef TVectorFrame<CInt4> CInt4Frame;
	class CTransform2DFrame
		:public TBaseObject<CTransform2DFrame>
		,public CFrameBase
		,public TMessageReceiver<CFrameBase>
	{
	protected:
		CFloat2Frame * mPosition;
		CFloatFrame * mRotation;
		CFloat2Frame * mScale;
	public:
		CTransform2DFrame();
		virtual ~CTransform2DFrame();
		Void setPosition(const CFloat2 & position);
		const CFloat2 & getPosition()const
		{
			if(mPosition)
				return mPosition->getValue();
			else
				return CFloat2::sZero;
		}
		Void setRotation(Float angle);
		Float getRotation()const
		{
			return mRotation->getValue();
		}
		Void setScale(const CFloat2 & scaleVec);
		const CFloat2 & getScale()const
		{
			if(mScale)
				return mScale->getValue();
			else
				return CFloat2::sOne;
		}
		virtual Void onMessage(CFrameBase * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
	};
	class CTransform3DFrame
		:public TBaseObject<CTransform3DFrame>
		,public CFrameBase
		,public TMessageReceiver<CFrameBase>
	{
	protected:
		CFloat3Frame * mPosition;
		CFloat4Frame * mRotation;
		CFloat3Frame * mScale;
	public:
		CTransform3DFrame();
		virtual ~CTransform3DFrame();
		Void setPosition(const CFloat3 & position);
		const CFloat3 & getPosition()const
		{
			if(mPosition)
				return mPosition->getValue();
			else
				return CFloat3::sZero;
		}
		Void setRotation(const CFloat4 & rotation);
		const CFloat4 & getRotation()const
		{
			return mRotation->getValue();
		}
		Void setScale(const CFloat3 & scale);
		const CFloat3 & getScale()const
		{
			if(mScale)
				return mScale->getValue();
			else
				return CFloat3::sOne;
		}
		virtual Void onMessage(CFrameBase * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
	};
}