#include "Precompiler.h"
using namespace NSDevilX;


CDegree::operator CRadian()const
{
	return CRadian(valueRadian());
}

CRadian::operator CDegree()const
{
	return CDegree(valueDegree());
}
