#pragma once
#include "IVertexBufferImp.h"
#include "IIndexBufferImp.h"
namespace NSDevilX
{
	namespace NSRenderSystem
	{
		class IGeometryImp
			:public IGeometry
			,public TBaseObject<IGeometryImp>
			,public CReferenceObject
			,public CMessageNotifier
			,public TMessageReceiver<IVertexBufferImp>
			,public TMessageReceiver<IIndexBufferImp>
		{
		public:
			enum EMessage
			{
				EMessage_BeginDestruction,
				EMessage_EndDestruction,
				EMessage_BeginVertexBufferChange,
				EMessage_EndVertexBufferChange,
				EMessage_BeginIndexBufferChange,
				EMessage_EndIndexBufferChange,
				EMessage_BeginNormalEnableChange,
				EMessage_EndNormalEnableChange,
				EMessage_BeginTangentEnableChange,
				EMessage_EndTangentEnableChange,
				EMessage_BeginTextureCoord0EnableChange,
				EMessage_EndTextureCoord0EnableChange,
				EMessage_BeginTextureCoord1EnableChange,
				EMessage_EndTextureCoord1EnableChange,
				EMessage_BeginDiffuseEnableChange,
				EMessage_EndDiffuseEnableChange
			};
		protected:
			const String mName;
			IVertexBufferImp * mVertexBuffer;
			IIndexBufferImp * mIndexBuffer;
		public:
			IGeometryImp(const String & name);
			// Inherited via IGeometry
			virtual const String & getName() const override;
			virtual Void setVertexBuffer(IVertexBuffer * buffer) override;
			virtual IVertexBuffer * getVertexBuffer() const override;
			virtual Void setIndexBuffer(IIndexBuffer * buffer) override;
			virtual IIndexBuffer * getIndexBuffer() const override;
		protected:
			~IGeometryImp();
			Void _registerToIVertexBufferImp();
			Void _unregisterToIVertexBufferImp();
			Void _registerToIIndexBufferImp();
			Void _unregisterToIIndexBufferImp();
			// Inherited via TMessageReceiver
			virtual Void onMessage(IVertexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;

			// Inherited via TMessageReceiver
			virtual Void onMessage(IIndexBufferImp * notifier,UInt32 message,VoidPtr data,Bool & needNextProcess) override;
		};
	}
}