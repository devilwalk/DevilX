#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IFile;
		class IFileProcesser
		{
		protected:
			virtual ~IFileProcesser(){}
		public:
			virtual IFile * getFile()const=0;
			virtual void setReadOffset(SizeT sizeInBytes)=0;
			virtual size_t getReadOffset()const=0;
			virtual size_t readBytes(SizeT sizeInBytes,OUT VoidPtr dst)=0;
			virtual void setWriteOffset(SizeT sizeInBytes)=0;
			virtual size_t getWriteOffset()const=0;
			virtual void writeBytes(ConstVoidPtr bytes,SizeT sizeInBytes)=0;
		};
	}
}