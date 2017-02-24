#pragma once
namespace NSDevilX
{
	namespace NSDevilCraft
	{
		class CGeometry
		{
		public:
			CGeometry()
			{
			}
			virtual ~CGeometry()
			{
			}
			virtual CFloat3 * getPositions()const=0;
			virtual CFloat3 * getNormals()const=0;
			virtual CFloat2 * getTextureCoords()const=0;
		};
	}
}