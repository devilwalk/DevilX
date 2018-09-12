#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IBuffer
		{
		protected:
			virtual ~IBuffer(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setSize(UInt32 sizeInBytes)=0;
			virtual UInt32 getSize()const=0;
			virtual Void setDatas(ConstVoidPtr datas)=0;
			virtual ConstVoidPtr getDatas()const=0;
			virtual Void updateData(UInt32 offsetInBytes=0,UInt32 sizeInBytes=0)=0;
			virtual Void bind(UInt32 offsetInBytes,IEnum::EAutoGPUPropgramParameterDataSource source)=0;
			virtual Void unbind(UInt32 offsetInBytes)=0;
			virtual IProgramBufferLayout * getLayout(IProgram * program,IEnum::EProgramResourceType resourceType,SizeT resourceIndex)=0;
		};
	}
}