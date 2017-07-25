#pragma once
#include "IBufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometryImp;
		class IIndexBufferImp
			:public IIndexBuffer
			,public TBaseObject<IIndexBufferImp>
			,public CDirtyFlagContainer
			,public CReferenceObject
			,public CMessageNotifier
		{
		protected:
			IBufferImp * mBuffer;
		public:
			IIndexBufferImp();
			IBufferImp * getBuffer()const
			{
				return mBuffer;
			}
			// Inherited via IIndexBuffer
			virtual Void setCount(UInt32 count) override;
			virtual UInt32 getCount() const override;
			virtual Void setIndices(const UInt32 * indices) override;
			virtual Void updateIndices(UInt32 offset=0,UInt32 count=0) override;
			virtual const UInt32 * getIndices() const override;
		protected:
			~IIndexBufferImp();
		};
	}
}