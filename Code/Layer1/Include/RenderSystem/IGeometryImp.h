#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBufferImp;
		class IGeometryImp;
		class IVertexBufferUsageImp
			:public TBaseObject<IVertexBufferUsageImp>
			,public IVertexBufferUsage
		{
		protected:
			IGeometryImp * const mGeometry;
			IBufferImp * mBuffer;
			IBufferUsageImp * mUsage;
			IEnum::EVertexElementFormat mFormat;
			String mSemanticName;
			UInt8 mAlignedOffset;
			UInt8 mStride;
			UInt8 mSemanticIndex;
		public:
			IVertexBufferUsageImp(IGeometryImp * geo);
			~IVertexBufferUsageImp();

			// 通过 IVertexBufferUsage 继承
			virtual IBufferUsage * queryInterface_IBufferUsage() const override;
			virtual IGeometry * getGeometry() const override;
			virtual Void setBuffer(IBuffer * buffer) override;
			virtual IBuffer * getBuffer() const override;
			virtual Void setFormat(UInt32 alignedByteOffset,IEnum::EVertexElementFormat format,const String & semanticName,UInt32 semanticIndex=0) override;
		};
		class IIndexBufferUsageImp
			:public TBaseObject<IIndexBufferUsageImp>
			,public IIndexBufferUsage
		{
		protected:
			IGeometryImp * const mGeometry;
			IBufferImp * mBuffer;
			IBufferUsageImp * mUsage;
			IEnum::EIndexFormat mFormat;
		public:
			IIndexBufferUsageImp(IGeometryImp * geo);
			~IIndexBufferUsageImp();

			// 通过 IIndexBufferUsage 继承
			virtual IBufferUsage * queryInterface_IBufferUsage() const override;
			virtual IGeometry * getGeometry() const override;
			virtual Void setBuffer(IBuffer * buffer) override;
			virtual IBuffer * getBuffer() const override;
			virtual Void setFormat(IEnum::EIndexFormat format) override;
		};
		class IGeometryImp
			:public IGeometry
			,public TBaseObject<IGeometryImp>
			,public CReferenceObject
		{
		protected:
			const String mName;
			TResourcePtrVector(IVertexBufferUsageImp) mVertexBufferUsages;
			IIndexBufferUsageImp * mIndexBufferUsage;
			IEnum::EOperationType mOperationType;
		public:
			IGeometryImp(const String & name);

			// 通过 IGeometry 继承
			virtual const String & getName() const override;
			virtual IVertexBufferUsage * getVertexBufferUsage(UInt32 slot) override;
			virtual IIndexBufferUsage * getIndexBufferUsage() override;
			virtual Void setOperationType(IEnum::EOperationType type) override;
			virtual IEnum::EOperationType getOperationType() const override;
		protected:
			~IGeometryImp();
		};
	}
}