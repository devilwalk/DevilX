#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IMaterialImp;
		class ITechniqueImp
			:public TBaseObject<ITechniqueImp>
			,public ITechnique
		{
		protected:
			const String mName;
			IMaterialImp * const mMaterial;
			String mSchemeName;
		public:
			ITechniqueImp(const String & name,IMaterialImp * material);
			~ITechniqueImp();

			// Í¨¹ý ITechnique ¼Ì³Ð
			virtual IMaterial * getMaterial() const override;
			virtual const String & getName() const override;
			virtual Void setSchemeName(const String & name) override;
			virtual const String getSchemeName() const override;
			virtual IPass * createPass() override;
			virtual IPass * getPass(UInt32 index) const override;
			virtual Void destroyPass(IPass * pass) override;
		};
	}
}