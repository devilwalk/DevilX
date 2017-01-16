#include "Precompiler.h"
using namespace NSDevilX;

const NSDevilX::CColour NSDevilX::CColour::sBlack(0.0f,0.0f,0.0f,1.0f);
const NSDevilX::CColour NSDevilX::CColour::sWhite(1.0f,1.0f,1.0f,1.0f);
const NSDevilX::CColour NSDevilX::CColour::sRed(1.0f,0.0f,0.0f,1.0f);
const NSDevilX::CColour NSDevilX::CColour::sGreen(0.0f,1.0f,0.0f,1.0f);
const NSDevilX::CColour NSDevilX::CColour::sBlue(0.0f,0.0f,1.0f,1.0f);
NSDevilX::CColour::CColour(UInt8 r,UInt8 g,UInt8 b,UInt8 a)
	:CFloat4(r/255.0f,g/255.0f,b/255.0f,a/255.0f)
{

}
