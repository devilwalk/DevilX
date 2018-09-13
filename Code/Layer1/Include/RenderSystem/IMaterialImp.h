#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IMaterialImp
			:public IMaterial
			,public TBaseObject<IMaterialImp>
		{
		protected:
			const String mName;
		public:
			IMaterialImp(const String & name);
			virtual ~IMaterialImp();

			// Í¨¹ý IMaterial ¼Ì³Ð
			virtual const String & getName() const override;
			virtual ITechnique * createTechnique(const String & name) override;
			virtual ITechnique * getTechnique(const String & name) override;
			virtual Void destroyTechnique(ITechnique * tech) override;
		};
	}
}