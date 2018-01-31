#pragma once
namespace NSDevilX
{
	namespace NSCubeBlockWorld
	{
		class CChunk
			:public TBaseObject<CChunk>
		{
		public:
			enum EState
			{
				EState_Unload,
				EState_Loading,
				EState_Loaded
			};
		protected:
			TSharedReadData<Int32> mLoadReferenceCount;
		public:
			CChunk();
			~CChunk();

			EState getStateMT();
			Void loadMT();
			Void unloadMT();
		};
	}
}