#pragma once
#include "ISceneElementImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ILightImp;
		class CLightProperty
			:public TMessageReceiver<ILightImp>
		{
		protected:
			ILightImp * const mLight;
		public:
			CLightProperty(ILightImp * light);
			virtual ~CLightProperty();
			ILightImp * getLight()const
			{
				return mLight;
			}
			// Inherited via TMessageReceiver
			virtual void onMessage(ILightImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
		class IDirectionLightPropertyImp
			:public IDirectionLightProperty
			,public TBaseObject<IDirectionLightPropertyImp>
			,public CLightProperty
			,public CDirtyFlagContainerMT
			,public TMessageReceiver<ISceneElementImp>
		{
		public:
			enum EDirtyFlag
			{
				EDirtyFlag_Direction
			};
		protected:
			CFloat3 mDirection;
		public:
			IDirectionLightPropertyImp(ILightImp * light);
			~IDirectionLightPropertyImp();
			const CFloat3 & getDirectionMT();
			// Inherited via IDirectionLightProperty
			virtual const CFloat3 & getDirection() const override;

			// Inherited via TMessageReceiver
			virtual Void onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;
		};
		class IPointLightPropertyImp
			:public IPointLightProperty
			,public TBaseObject<IPointLightPropertyImp>
			,public CMessageNotifier
			,public CLightProperty
			,public CDirtyFlagContainerMT
			,public TMessageReceiver<ISceneElementImp>
		{
		public:
			enum EMessage
			{
				EMessage_RangeChange
			};
			enum EDirtyFlag
			{
				EDirtyFlag_Bound
			};
		protected:
			DirectX::BoundingSphere mBound;
		public:
			IPointLightPropertyImp(ILightImp * light);
			virtual ~IPointLightPropertyImp();
			decltype(mBound) const & getBoundMT();
			// Inherited via IPointLightProperty
			virtual Float getRange() const override;
		protected:
			virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;

			// Inherited via TMessageReceiver
			virtual Void onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
		class ISpotLightPropertyImp
			:public ISpotLightProperty
			,public TBaseObject<ISpotLightPropertyImp>
			,public CMessageNotifier
			,public CLightProperty
			,public CDirtyFlagContainerMT
			,public TMessageReceiver<ISceneElementImp>
		{
			enum EMessage
			{
				EMessage_BeginAngleChange,
				EMessage_EndAngleChange,
				EMessage_RangeChange,
				EMessage_DirectionChange
			};
			enum EDirtyFlag
			{
				EDirtyFlag_Bound,
				EDirtyFlag_Direction
			};
		protected:
			CFloat3 mDirection;
			CDegree mAngle;
			CPlaneBoundedVolume mBound;
		public:
			ISpotLightPropertyImp(ILightImp * light);
			virtual ~ISpotLightPropertyImp();
			decltype(mBound) const & getBoundMT();
			const CFloat3 & getDirectionMT();
			// Inherited via ISpotLightProperty
			virtual const CFloat3 & getDirection() const override;
			virtual Float getRange() const override;
			virtual void setAngle(const CDegree & angle) override;
			virtual const CDegree & getAngle() const override;
		protected:
			virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;
			// Inherited via TMessageReceiver
			virtual Void onMessage(ISceneElementImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
		class ISceneImp;
		class ILightImp
			:public ILight
			,public TBaseObject<ILightImp>
			,public CMessageNotifier
			,public CUserDataContainer
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginColourChange,
				EMessage_EndColourChange,
				EMessage_BeginShadowEnableChange,
				EMessage_EndShadowEnableChange
			};
		protected:
			const IEnum::ELightType mType;
			ISceneElementImp * mSceneElement;
			union
			{
				IDirectionLightPropertyImp * mDirectionLightProperty;
				IPointLightPropertyImp * mPointLightProperty;
				ISpotLightPropertyImp * mSpotLightProperty;
			};
			CColour mColour;
			Bool mShadowEnable;
			TVector<IRenderableObjectImp*> mVisibleRenderableObjects;
			TSharedReadData<UInt32> mVisibleElementsFrameIndex;
		public:
			ILightImp(const String & name,IEnum::ELightType type,ISceneImp * scene);
			virtual ~ILightImp();
			decltype(mVisibleRenderableObjects) const & getVisibleRenderableObjects()const
			{
				return mVisibleRenderableObjects;
			}
			Void findVisibleObjectsMT();
			// Inherited via ILight
			virtual ISceneElement * queryInterface_ISceneElement() const override;
			virtual IDirectionLightProperty * queryInterface_IDirectionLightProperty() const override;
			virtual IPointLightProperty * queryInterface_IPointLightProperty() const override;
			virtual ISpotLightProperty * queryInterface_ISpotLightProperty() const override;
			virtual IEnum::ELightType getType() const override;
			virtual Void setColour(const CColour & colour) override;
			virtual const CColour & getColour() const override;
			virtual Void setShadowEnable(Bool enable) override;
			virtual Bool getShadowEnable() const override;
		};
	}
}