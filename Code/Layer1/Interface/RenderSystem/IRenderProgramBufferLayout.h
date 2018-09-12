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
			virtual SizeT getOffset(const String & name)const=0;
			virtual SizeT getSize(const String & name)const=0;
		};
	}
}