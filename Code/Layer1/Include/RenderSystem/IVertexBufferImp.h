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
			struct SDirties
				:public CRangesI
			{
				using CRangesI::CRangesI;
				Void addDirty(UInt32 offset,UInt32 count)
				{
					addRange(CRangeI(offset,count+offset-1));
				}
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
			SDirties mPositionsDirty;
			SDirties mNormalsDirty;
			SDirties mTangentsDirty;
			SDirties mTextureCoordsDirty[2];
			SDirties mBlendWeightsDirty;
			SDirties mBlendIndicesDirty;
			SDirties mDiffusesDirty;
		public:
			IVertexBufferImp();
			const SDirties & getPositionsDirties()const
			{
				return mPositionsDirty;
			}
			const SDirties & getNormalsDirties()const
			{
				return mNormalsDirty;
			}
			const SDirties & getTangentsDirties()const
			{
				return mTangentsDirty;
			}
			const SDirties & getTextureCoordsDities(IEnum::ETextureCoord index=IEnum::ETextureCoord_0)const
			{
				return mTextureCoordsDirty[index];
			}
			const SDirties & getBlendWeightsDirties()const
			{
				return mBlendWeightsDirty;
			}
			const SDirties & getBlendIndicesDirties()const
			{
				return mBlendIndicesDirty;
			}
			const SDirties & getDiffusesDirties()const
			{
				return mDiffusesDirty;
			}
			const CFloat3 * const & getPositionsRef()const
			{
				return mPositions;
			}
			const CFloat3 * const & getNormalsRef()const
			{
				return mNormals;
			}
			const CFloat3 * const & getTangentsRef()const
			{
				return mTangents;
			}
			const CFloat2 * const & getTextureCoordsRef(IEnum::ETextureCoord index=IEnum::ETextureCoord_0)const
			{
				return mTextureCoords[IEnum::ETextureCoord_0];
			}
			const CFloat4 * const & getBlendWeightsRef()const
			{
				return mBlendWeights;
			}
			const UInt8 * const & getBlendIndicesRef()const
			{
				return mBlendIndices;
			}
			const RGBA * const & getDiffusesRef()const
			{
				return mDiffuses;
			}
			virtual Void setCount(UInt32 count) override;
			virtual UInt32 getCount() const override;
			virtual Void setPositions(const CFloat3 * positions,UInt32 count=0) override;
			virtual Void updatePositions(UInt32 offset=0,UInt32 count=0) override;
			virtual const CFloat3 * getPositions() const override;
			virtual Void setNormals(const CFloat3 * normals,UInt32 count=0) override;
			virtual Void updateNormals(UInt32 offset=0,UInt32 count=0) override;
			virtual const CFloat3 * getNormals() const override;
			virtual Void setTangents(const CFloat3 * tangents,UInt32 count=0) override;
			virtual Void updateTangents(UInt32 offset=0,UInt32 count=0) override;
			virtual const CFloat3 * getTangents() const override;
			virtual Void setTextureCoords(const CFloat2 * uvs,UInt32 count=0,IEnum::ETextureCoord index=IEnum::ETextureCoord_0) override;
			virtual Void updateTextureCoords(UInt32 offset=0,UInt32 count=0,IEnum::ETextureCoord index=IEnum::ETextureCoord_0) override;
			virtual const CFloat2 * getTextureCoords(IEnum::ETextureCoord index=IEnum::ETextureCoord_0) const override;
			virtual Void setBlendWeights(const CFloat4 * blendWeights,UInt32 count=0) override;
			virtual Void updateBlendWeights(UInt32 offset=0,UInt32 count=0) override;
			virtual const CFloat4 * getBlendWeights() const override;
			virtual Void setBlendIndices(const UInt8 * blendIndices,UInt32 count=0) override;
			virtual Void updateBlendIndices(UInt32 offset=0,UInt32 count=0) override;
			virtual const UInt8 * getBlendIndices() const override;
			virtual Void setDiffuses(const RGBA * colours,UInt32 count=0) override;
			virtual Void updateDiffuses(UInt32 offset=0,UInt32 count=0) override;
			virtual const RGBA * getDiffuses() const override;
		protected:
			~IVertexBufferImp();
			virtual Void _preProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagAdd(UInt32 flagIndex) override;
			virtual Void _postProcessDirtyFlagRemove(UInt32 flagIndex) override;
		};
	}
}