#pragma once
namespace NSDevilX
{
	namespace NSResourceSystem
	{
		class IResourceImp
			:public TBaseObject<IResourceImp>
			,public IResource
		{
		protected:
			const String mName;
			const String mFile;
		public:
			IResourceImp(const String & name,const String & file);
			~IResourceImp();

			// ͨ�� IResource �̳�
			virtual const String & getName() const override;
			virtual const String & getFileName() const override;
		};
	}
}