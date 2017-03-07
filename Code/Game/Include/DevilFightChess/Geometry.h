#pragma once
namespace NSDevilX
{
	namespace NSFightChess
	{
		class CGeometry
		{
		protected:
			TVector<CFloat3> mPositions;
			TVector<CFloat3> mNormals;
			TVector<CFloat2> mTextureCoords;
			TVector<UInt32> mIndices;
			NSRenderSystem::IGeometry * mRenderGeometry;
		public:
			CGeometry();
			virtual ~CGeometry();
			NSRenderSystem::IGeometry * getRenderGeometry()const
			{
				return mRenderGeometry;
			}
		};
		//Ê®×Ö½»²æ²ÝµØ
		class CGrasses
			:public CGeometry
			,public TBaseObject<CGrasses>
		{
		protected:
		public:
			CGrasses();
			~CGrasses();
		};
	}
}