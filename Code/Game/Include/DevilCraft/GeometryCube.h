#pragma once
#include "Geometry.h"
namespace NSDevilX
{
	namespace NSDevilCraft
	{
		class CGeometryCube
			:public CGeometry
			,public TBaseObject<CGeometryCube>
		{
			struct SVertex
			{
				CFloat3 mPosition;
				CFloat3 mNormal;
				CFloat2 mTextureCoord;
			};
		protected:
			SVertex mVertices[24];
			UInt32 mIndices[36];
		public:
			CGeometryCube()
			{
				mVertices[0].mPosition=CFloat3(-1.0f,1.0f,1.0f);
				mVertices[1].mPosition=CFloat3(1.0f,1.0f,1.0f);
				mVertices[2].mPosition=CFloat3(-1.0f,1.0f,-1.0f);
				mVertices[3].mPosition=CFloat3(1.0f,1.0f,-1.0f);
				mVertices[4].mPosition=CFloat3(-1.0f,-1.0f,-1.0f);
				mVertices[5].mPosition=CFloat3(1.0f,-1.0f,-1.0f);
				mVertices[6].mPosition=CFloat3(-1.0f,-1.0f,1.0f);
				mVertices[7].mPosition=CFloat3(1.0f,-1.0f,1.0f);
				mVertices[8].mPosition=CFloat3(-1.0f,1.0f,1.0f);
				mVertices[9].mPosition=CFloat3(-1.0f,1.0f,-1.0f);
				mVertices[10].mPosition=CFloat3(-1.0f,-1.0f,1.0f);
				mVertices[11].mPosition=CFloat3(-1.0f,-1.0f,-1.0f);
				mVertices[12].mPosition=CFloat3(1.0f,1.0f,-1.0f);
				mVertices[13].mPosition=CFloat3(1.0f,1.0f,1.0f);
				mVertices[14].mPosition=CFloat3(1.0f,-1.0f,-1.0f);
				mVertices[15].mPosition=CFloat3(1.0f,-1.0f,1.0f);
				mVertices[16].mPosition=CFloat3(-1.0f,1.0f,-1.0f);
				mVertices[17].mPosition=CFloat3(1.0f,1.0f,-1.0f);
				mVertices[18].mPosition=CFloat3(-1.0f,-1.0f,-1.0f);
				mVertices[19].mPosition=CFloat3(1.0f,-1.0f,-1.0f);
				mVertices[20].mPosition=CFloat3(1.0f,1.0f,1.0f);
				mVertices[21].mPosition=CFloat3(-1.0f,1.0f,1.0f);
				mVertices[22].mPosition=CFloat3(1.0f,-1.0f,1.0f);
				mVertices[23].mPosition=CFloat3(-1.0f,-1.0f,1.0f);
				mVertices[0].mNormal=CFloat3::sUnitY;
				mVertices[1].mNormal=CFloat3::sUnitY;
				mVertices[2].mNormal=CFloat3::sUnitY;
				mVertices[3].mNormal=CFloat3::sUnitY;
				mVertices[4].mNormal=-CFloat3::sUnitY;
				mVertices[5].mNormal=-CFloat3::sUnitY;
				mVertices[6].mNormal=-CFloat3::sUnitY;
				mVertices[7].mNormal=-CFloat3::sUnitY;
				mVertices[8].mNormal=-CFloat3::sUnitX;
				mVertices[9].mNormal=-CFloat3::sUnitX;
				mVertices[10].mNormal=-CFloat3::sUnitX;
				mVertices[11].mNormal=-CFloat3::sUnitX;
				mVertices[12].mNormal=CFloat3::sUnitX;
				mVertices[13].mNormal=CFloat3::sUnitX;
				mVertices[14].mNormal=CFloat3::sUnitX;
				mVertices[15].mNormal=CFloat3::sUnitX;
				mVertices[16].mNormal=-CFloat3::sUnitZ;
				mVertices[17].mNormal=-CFloat3::sUnitZ;
				mVertices[18].mNormal=-CFloat3::sUnitZ;
				mVertices[19].mNormal=-CFloat3::sUnitZ;
				mVertices[20].mNormal=CFloat3::sUnitZ;
				mVertices[21].mNormal=CFloat3::sUnitZ;
				mVertices[22].mNormal=CFloat3::sUnitZ;
				mVertices[23].mNormal=CFloat3::sUnitZ;
				for(UInt32 i=0;i<6;++i)
				{
					mVertices[i*4].mTextureCoord=CFloat2::sZero;
					mVertices[i*4+1].mTextureCoord=CFloat2(1.0f,0.0f);
					mVertices[i*4+2].mTextureCoord=CFloat2(0.0f,1.0f);
					mVertices[i*4+3].mTextureCoord=CFloat2(1.0f,1.0f);
				}
				for(UInt32 i=0;i<6;++i)
				{
					mIndices[i*6]=i*4;
					mIndices[i*6+1]=i*4+1;
					mIndices[i*6+2]=i*4+2;
					mIndices[i*6+3]=i*4+2;
					mIndices[i*6+4]=i*4+1;
					mIndices[i*6+5]=i*4+3;
				}
			}
			~CGeometryCube()
			{

			}
		};
	}
}