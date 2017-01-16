#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ISceneImp;
		class IVisibleAreaImp
			:public IVisibleArea
			,public TBaseObject<IVisibleAreaImp>
			,public CMessageNotifier
			,public TMessageReceiver<ITransformerImp>
			,public CDirtyFlagContainerMT
		{
		public:
			enum EMessage
			{
				EMessage_BeginVisibleChange,
				EMessage_EndVisibleChange,
				EMessage_BeginTransformerChange,
				EMessage_EndTransformerChange,
				EMessage_BeginWorldBoundingBoxChange,
				EMessage_EndWorldBoundingBoxChange,
				EMessage_BeginObjectAttach,
				EMessage_EndObjectAttach,
				EMessage_BeginObjectDetach,
				EMessage_EndObjectDetach
			};
			enum EDirtyFlag
			{
				EDirtyFlag_WorldAABB
			};
		protected:
			const String mName;
			ISceneImp * const mScene;
			Bool mVisible;
			ITransformerImp * mTransformer;
			DirectX::BoundingBox mLocalAABB;
			DirectX::BoundingBox mWorldAABB;
			TSet<ISceneElementImp*> mObjects;
		public:
			IVisibleAreaImp(const String & name,ISceneImp * scene);
			virtual ~IVisibleAreaImp();
			const DirectX::BoundingBox & getWorldBoundingBox();
			const decltype(mObjects) & getAttachedObjects()const
			{
				return mObjects;
			}
			// Inherited via IVisibleArea
			virtual const String & getName() const override;
			virtual IScene * getScene() const override;
			virtual Void setVisible(Bool visible) override;
			virtual Bool getVisible() const override;
			virtual Void setTransformer(ITransformer * transformer) override;
			virtual ITransformer * getTransformer() const override;
			virtual Void setBoundingBox(const DirectX::BoundingBox & aabb) override;
			virtual const DirectX::BoundingBox & getBoundingBox() const override;
			virtual Void attachObject(ISceneElement * element) override;
			virtual Void detachObject(ISceneElement * element) override;
		protected:
			Void _updateWorldAABB();

			// Inherited via TMessageReceiver
			virtual Void onMessage(ITransformerImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
			virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess);
		};
	}
}