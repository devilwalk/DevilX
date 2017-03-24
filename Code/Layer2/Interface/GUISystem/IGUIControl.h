#pragma once
namespace NSDevilX
{
	namespace NSGUISystem
	{
		class IWindow;
		class IControl
		{
		protected:
			virtual ~IControl(){}
		public:
			virtual const String & getName()const=0;
			virtual Void setPosition(const CFloat2 & position)=0;
			virtual const CFloat2 & getPosition()const=0;
			virtual Void setSize(const CFloat2 & size)=0;
			virtual const CFloat2 & getSize()const=0;
			virtual IWindow * getParentWindow()const=0;
		};
	}
}