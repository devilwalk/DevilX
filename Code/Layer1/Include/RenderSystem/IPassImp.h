#pragma once
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class ITechniqueImp;
		class IPassImp
			:public IPass
			,public TBaseObject<IPassImp>
		{
		protected:
			ITechniqueImp * const mTechnique;
		public:
			IPassImp(ITechniqueImp * technique);
			~IPassImp();

			// Í¨¹ý IPass ¼Ì³Ð
			virtual ITechnique * getTechnique() const override;
			virtual Void setProgram(IProgram * program) override;
			virtual IProgram * getProgram() const override;
			virtual Void setProgramResource(UInt32 resourceLocation,IBuffer * buffer) override;
			virtual Void setProgramResource(UInt32 resourceLocation,ITexture * texture) override;
			virtual Void setProgramResource(UInt32 resourceLocation,ISamplerState * state) override;
		};
	}
}