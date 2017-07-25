#pragma once
#include "IBufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometryImp;
		class IVertexBufferImp
			:public IVertexBuffer
			,public TBaseObject<IVertexBufferImp>
			,public CMessageNotifier
			,public CReferenceObject
		{
		public:
			enum EMessage
			{
				EMessage_BeginPositionEnableChange,
				EMessage_EndPositionEnableChange,
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
				EMessage_BeginBlendWeightEnableChange,
				EMessage_EndBlendWeightEnableChange,
				EMessage_BeginBlendIndexEnableChange,
				EMessage_EndBlendIndexEnableChange
			};
			enum EBufferType
			{
				EBufferType_Position,
				EBufferType_Normal,
				EBufferType_Tangent,
				EBufferType_TextureCoord0,
				EBufferType_TextureCoord1,
				EBufferType_BlendWeight,
				EBufferType_BlendIndex,
				EBufferType_Diffuse,
				EBufferType_Count
			};
		protected:
			UInt32 mCount;
			std::array<IBufferImp*,EBufferType_Count> mBuffers;
		public:
			static UInt32 getStride(UInt32 index)
			{
				UInt32 ret=0;
				switch(index)
				{
				case EBufferType_Position:
				case EBufferType_Normal:
				case EBufferType_Tangent:
					ret=sizeof(CFloat3);
					break;
				case EBufferType_BlendWeight:
					ret=sizeof(CFloat4);
					break;
				case EBufferType_TextureCoord0:
				case EBufferType_TextureCoord1:
					ret=sizeof(CFloat2);
					break;
				case EBufferType_BlendIndex:
				case EBufferType_Diffuse:
					ret=sizeof(UInt32);
					break;
				default:
					assert(0);
				}
				return ret;
			}
			IVertexBufferImp();
			IBufferImp * getBuffer(UInt32 index)const
			{
				return mBuffers[index];
			}
			virtual Void setCount(UInt32 count) override;
			virtual UInt32 getCount() const override;
			virtual Void setPositions(const CFloat3 * positions) override;
			virtual Void updatePositions(UInt32 offset=0,UInt32 count=0) override;
			virtual const CFloat3 * getPositions() const override;
			virtual Void setNormals(const CFloat3 * normals) override;
			virtual Void updateNormals(UInt32 offset=0,UInt32 count=0) override;
			virtual const CFloat3 * getNormals() const override;
			virtual Void setTangents(const CFloat3 * tangents) override;
			virtual Void updateTangents(UInt32 offset=0,UInt32 count=0) override;
			virtual const CFloat3 * getTangents() const override;
			virtual Void setTextureCoords(const CFloat2 * uvs,IEnum::ETextureCoord index=IEnum::ETextureCoord_0) override;
			virtual Void updateTextureCoords(UInt32 offset=0,UInt32 count=0,IEnum::ETextureCoord index=IEnum::ETextureCoord_0) override;
			virtual const CFloat2 * getTextureCoords(IEnum::ETextureCoord index=IEnum::ETextureCoord_0) const override;
			virtual Void setBlendWeights(const CFloat4 * blendWeights) override;
			virtual Void updateBlendWeights(UInt32 offset=0,UInt32 count=0) override;
			virtual const CFloat4 * getBlendWeights() const override;
			virtual Void setBlendIndices(const UInt8 * blendIndices) override;
			virtual Void updateBlendIndices(UInt32 offset=0,UInt32 count=0) override;
			virtual const UInt8 * getBlendIndices() const override;
			virtual Void setDiffuses(const RGBA * colours) override;
			virtual Void updateDiffuses(UInt32 offset=0,UInt32 count=0) override;
			virtual const RGBA * getDiffuses() const override;
		protected:
			~IVertexBufferImp();
			Void _updateBuffer(UInt32 index,UInt32 offset=0,UInt32 count=0);
			template<typename TReturn>
			const TReturn * _getData(UInt32 index)const
			{
				return getBuffer(index)?static_cast<const TReturn*>(getBuffer(index)->getDatas()):nullptr;
			}
		};
	}
}