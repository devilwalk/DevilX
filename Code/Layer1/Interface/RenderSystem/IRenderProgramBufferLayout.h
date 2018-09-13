#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IProgramBufferLayout
		{
		protected:
			virtual ~IProgramBufferLayout(){ }
		public:
			virtual UInt32 getOffset(const String & name)const=0;
			virtual UInt32 getSize(const String & name)const=0;
		};
	}
}