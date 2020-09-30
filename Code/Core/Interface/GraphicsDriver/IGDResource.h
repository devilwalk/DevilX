#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		namespace NSGraphicsDriver
		{
			class IBufferView
			{
			protected:
				virtual ~IBufferView(){}
			public:
			};

			class IBuffer
			{
			protected:
				virtual ~IBuffer(){}
			public:
				virtual IBufferView* createView(const VkBufferViewCreateInfo& info)=0;
			};

			class IImageView
			{
			protected:
				virtual ~IImageView(){}
			public:
			};

			class IImage
			{
			protected:
				virtual ~IImage(){}
			public:
				virtual IImageView* createView(const VkImageViewCreateInfo& info)=0;
			};
		}
	}
}