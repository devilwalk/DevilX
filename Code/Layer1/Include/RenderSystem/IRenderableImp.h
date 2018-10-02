#include "IMaterialImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometryUsageImp
			:public TBaseObject<IGeometryUsageImp>
			,public IGeometryUsage
		{
		protected:
			UInt32 mStartIndexLocation;
			UInt32 mIndexCount;
			UInt32 mBaseVertexLocation;
			UInt32 mVertexCount;
			UInt32 mStartVertexLocation;
		public:
			IGeometryUsageImp();
			~IGeometryUsageImp();

			virtual Void setStartIndexLocation(UInt32 location) override;
			virtual UInt32 getStartIndexLocation() const override;
			virtual Void setIndexCount(UInt32 count) override;
			virtual UInt32 getIndexCount() const override;
			virtual Void setBaseVertexLocation(UInt32 location) override;
			virtual UInt32 getBaseVertexLocation() const override;
			virtual Void setVertexCount(UInt32 count) override;
			virtual UInt32 getVertexCount() const override;
			virtual Void setStartVertexLocation(UInt32 location) override;
			virtual UInt32 getStartVertexLocation() const override;
		};
		class IRenderableImp
			:public IRenderable
			,public TBaseObject<IRenderableImp>
		{
		protected:
			IGeometryImp * mGeometry;
			IGeometryUsageImp * mGeometryUsage;
			IMaterialImp * mMaterial;
			Bool mVisible;
		public:
			IRenderableImp();
			~IRenderableImp();

			// Í¨¹ý IRenderable ¼Ì³Ð
			virtual IGeometryUsage * queryInterface_IGeometryUsage() const override;
			virtual Void setGeometry(IGeometry * geometry) override;
			virtual IGeometry * getGeometry() const override;
			virtual Void setVisible(Bool visible) override;
			virtual Bool getVisible() const override;
			virtual Void setMaterial(IMaterial * material) override;
			virtual IMaterial * getMaterial() const override;
		};
	}
}