#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometryImp;
		class IVertexBufferImp
			:public IVertexBuffer
			,public TBaseObject<IVertexBufferImp>
			,public CMessageNotifier
			,public CDirtyFlagContainer
			,public CReferenceObject
		{
		public:
			enum EMessage
			{
				EMessage_BeginNormalEnableChange,
				EMessage_EndNormalEnableChange,
				EMessage_BeginTangentEnableChange,
				EMessage_EndTangentEnableChange,
				EMessage_BeginTextureCoord0EnableChange,
				EMessage_EndTextureCoord0EnableChange,
				EMessage_BeginTextureCoord1EnableChange,
				EMessage_EndTextureCoord1EnableChange,
				EMessage_BeginDiffuseEnableChange,
				EMessage_EndDiffuseEnableChange,
				EMessage_BeginDirtyFlagAdd,
				EMessage_EndDirtyFlagAdd
			};
			enum EDirtyFlag
			{
				EDirtyFlag_Count,
				EDirtyFlag_Position,
				EDirtyFlag_Normal,
				EDirtyFlag_Tangent,
				EDirtyFlag_TextureCoord0,
				EDirtyFlag_TextureCoord1,
				EDirtyFlag_BlendWeight,
				EDirtyFlag_BlendIndex,
				EDirtyFlag_Diffuse
			};
		protected:
			UInt32 mCount;
			const CFloat3 * mPositions;
			const CFloat3 * mNormals;
			const CFloat3 * mTangents;
			const CFloat2 * mTextureCoords[2];
			const CFloat4 * mBlendWeights;
			const UInt8 * mBlendIndices;
			const RGBA * mDiffuses;
		public:
			IVertexBufferImp();

			virtual Void setCount(UInt32 count) override;
			virtual UInt32 getCount() const override;
			virtual Void setPositions(const CFloat3 * positions) override;
			virtual Void updatePositions() override;
			virtual const CFloat3 * getPositions() const override;
			virtual Void setNormals(const CFloat3 * normals) override;
			virtual Void updateNormals() override;
			virtual const CFloat3 * getNormals() const override;
			virtual Void setTangents(const CFloat3 * tangents) override;
			virtual Void updateTangents() override;
			virtual const CFloat3 * getTangents() const override;
			virtual Void setTextureCoords(const CFloat2 * uvs,IEnum::ETextureCoord index=IEnum::ETextureCoord_0) override;
			virtual Void updateTextureCoords(IEnum::ETextureCoord index=IEnum::ETextureCoord_0) override;
			virtual const CFloat2 * getTextureCoords(IEnum::ETextureCoord index=IEnum::ETextureCoord_0) const override;
			virtual Void setBlendWeights(const CFloat4 * blendWeights) override;
			virtual Void updateBlendWeights() override;
			virtual const CFloat4 * getBlendWeights() const override;
			virtual Void setBlendIndices(const UInt8 * blendIndices) override;
			virtual Void updateBlendIndices() override;
			virtual const UInt8 * getBlendIndices() const override;
			virtual Void setDiffuses(const RGBA * colours) override;
			virtual Void updateDiffuses() override;
			virtual const RGBA * getDiffuses() const override;
		protected:
			~IVertexBufferImp();
			virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex) override;
		};
	}
}