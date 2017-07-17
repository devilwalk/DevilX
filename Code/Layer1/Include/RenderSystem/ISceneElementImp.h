#pragma once
#include "ITransformerImp.h"
#include "ICommonUserDataContainerImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISceneImp;
		class ISceneElementImp
			:public ISceneElement
			,public TBaseObject<ISceneElementImp>
			,public CMessageNotifier
			,public CUserDataContainer
			,public TMessageReceiver<ITransformerImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginTransformerChange,
				EMessage_EndTransformerChange,
				//transformer
				EMessage_PositionChange,
				EMessage_OrientationChange,
				EMessage_ScaleChange,
				EMessage_Count
			};
			enum EContainerObjectType
			{
				EContainerObjectType_Entity,
				EContainerObjectType_Light,
				EContainerObjectType_Camera,
				EContainerObjectType_Sky,
				EContainerObjectType_QueryObject
			};
		protected:
			const String mName;
			ISceneImp * const mScene;
			VoidPtr const mContainerObject;
			const EContainerObjectType mContainerObjectType;
			ITransformerImp * mTransformer;
		public:
			ISceneElementImp(const String & name,ISceneImp * scene,VoidPtr containerObject,EContainerObjectType type);
			virtual ~ISceneElementImp();
			template<class T>
			T * getContainerObject()const
			{
				return static_cast<T*>(mContainerObject);
			}
			EContainerObjectType getContainerObjectType()const
			{
				return mContainerObjectType;
			}
			virtual const String & getName() const override;

			virtual IScene * getScene() const override;

			virtual Void setTransformer(ITransformer * transformer) override;

			virtual ITransformer * getTransformer() const override;

			// Inherited via TMessageReceiver
			virtual Void onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		protected:
			Void _registerToITransformerImp();
			Void _unregisterToITransformerImp();
		};
	}
}