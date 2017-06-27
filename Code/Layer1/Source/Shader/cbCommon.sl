#include "Defines.sl"
DECL_CB(cbSystem)
CB_MEMBER float gFrameTimeInSeconds;
CB_MEMBER float gInverseFrameTimeInSeconds;
END_DECL
DECL_CB(cbRenderTarget)
CB_MEMBER float2 gRenderTargetSizeInPixel;
CB_MEMBER float2 gInverseRenderTargetSizeInPixel;
END_DECL
DECL_CB(cbViewport)
CB_MEMBER float2 gViewportSizeInPixel;
CB_MEMBER float2 gInverseViewportSizeInPixel;
END_DECL
DECL_CB(cbCamera)
CB_MEMBER float4x4 gViewMatrix;
CB_MEMBER float4x4 gInverseViewMatrix;
CB_MEMBER float4x4 gProjectionMatrix;
CB_MEMBER float4x4 gInverseProjectionMatrix;
CB_MEMBER float4x4 gViewProjectionMatrix;
CB_MEMBER float4x4 gInverseViewProjectionMatrix;
CB_MEMBER float gFarDistance;
CB_MEMBER float gInverseFarDistance;
END_DECL
DECL_CB(cbScene)
CB_MEMBER float3 gAmbientColour;
CB_MEMBER float3 gSkyColour;
CB_MEMBER float3 gGroundColour;
CB_MEMBER float3 gSkyLightDirection;
END_DECL
