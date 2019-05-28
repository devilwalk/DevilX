#pragma once
namespace NSDevilX
{
	namespace NSCore
	{
		class IGACommandGroup_3D
		{
		protected:
			virtual ~IGACommandGroup_3D()
			{
			}
		public:
		};
		class IGACommandGroup_Compute
		{
		protected:
			virtual ~IGACommandGroup_Compute()
			{
			}
		public:
		};
		class IGACommandGroup_Copy
		{
		protected:
			virtual ~IGACommandGroup_Copy()
			{
			}
		public:
		};
		class IGACommandList_3D
		{
		protected:
			virtual ~IGACommandList_3D(){ }
		public:
			virtual IGACommandGroup_3D* queryInterface_IGACommandGroup_3D()const=0;
			virtual IGACommandGroup_Compute* queryInterface_IGACommandGroup_Compute()const=0;
			virtual IGACommandGroup_Copy* queryInterface_IGACommandGroup_Copy()const=0;
		};
		class IGACommandList_Compute
		{
		protected:
			virtual ~IGACommandList_Compute(){ }
		public:
			virtual IGACommandGroup_Compute* queryInterface_IGACommandGroup_Compute()const=0;
			virtual IGACommandGroup_Copy* queryInterface_IGACommandGroup_Copy()const=0;
		};
		class IGACommandList_Copy
		{
		protected:
			virtual ~IGACommandList_Copy(){ }
		public:
			virtual IGACommandGroup_Copy* queryInterface_IGACommandGroup_Copy()const=0;
		};
	}
}