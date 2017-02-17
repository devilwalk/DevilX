#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITransformerImp
			:public ITransformer
			,public CMessageNotifier
			,public TBaseObject<ITransformerImp>
			,public NSDevilX::CDirtyFlagContainerMT
			,public CReferenceObject
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginPositionChange,
				EMessage_EndPositionChange,
				EMessage_BeginOrientationChange,
				EMessage_EndOrientationChange,
				EMessage_BeginScaleChange,
				EMessage_EndScaleChange,
				EMessage_Count
			};
			enum EDirtyFlag
			{
				EDirtyFlag_Transform
			};
		protected:
			CFloat3 mPosition,mScale;
			CFloat4 mOrientation;
			CMatrix4F mTransform;
		public:
			ITransformerImp();
			~ITransformerImp();
			const CMatrix4F & getTransformMT();

			virtual Void setPosition(const CFloat3 & pos) override;

			virtual const CFloat3 & getPosition() const override;

			virtual Void setOrientation(const CFloat4 & orientation) override;

			virtual const CFloat4 & getOrientation() const override;

			virtual Void setScale(const CFloat3 & scale) override;

			virtual const CFloat3 & getScale() const override;
		protected:
			virtual Boolean _process(UInt32 flagIndex,OUT Bool & needNextProcess) override;
		};
	}
}