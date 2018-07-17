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
			virtual void setReadOffset(size_t sizeInBytes)=0;
			virtual size_t getReadOffset()const=0;
			virtual size_t readBytes(void * dst,size_t sizeInBytes)=0;
			virtual void setWriteOffset(size_t sizeInBytes)=0;
			virtual size_t getWriteOffset()const=0;
			virtual void writeBytes(const void * bytes,size_t sizeInBytes)=0;
		};
	}
}