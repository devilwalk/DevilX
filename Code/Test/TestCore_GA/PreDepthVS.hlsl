StructuredBuffer<float4> gPositionBuffer:register(t0);
StructuredBuffer<uint4> gIndexBuffer:register(t1);

struct SObjectBuffer
{
	float4x4 mWVPMatrix;
};
StructuredBuffer<SObjectBuffer> gObjectBuffer:register(t2);

cbuffer cbInstances:register(b0)
{
	uint4 gInstances[4096];
};

struct SInputVS
{
	uint mInstanceID:SV_InstanceID;
	uint mVertexID:SV_VertexID;
};

struct SOutputVS
{
	float4 mTarget:SV_Position;
	//uint4 mTest0:TEST0;
	//uint4 mTest1:TEST1;
};

void main(SInputVS input,out SOutputVS output)
{
	//output.mTest0=0;
	//output.mTest1=0;
	//output.mTest0.x=input.mInstanceID;
	//output.mTest0.y=input.mVertexID;
	uint4 instance_data=gInstances[input.mInstanceID/2];
	uint component_index=(input.mInstanceID%2)*2;
	uint index_start=instance_data[component_index];
	uint index_count=instance_data[component_index+1];
	if(input.mVertexID<index_count)
	{
		uint vertex_index=input.mVertexID+index_start;
		uint index_buffer_index=vertex_index/4;
		uint4 index_buffer=gIndexBuffer.Load(index_buffer_index);
		uint index_buffer_componet=vertex_index%4;
		uint index=index_buffer[index_buffer_componet];
		float3 position=gPositionBuffer.Load(index).xyz;
		//output.mTarget=float4(position,1.0);
		SObjectBuffer object_buffer=gObjectBuffer.Load(input.mInstanceID);
		output.mTarget=mul(float4(position,1.0),object_buffer.mWVPMatrix);

		//output.mTest0.z=vertex_index;
		//output.mTest0.w=index_buffer_index;
		//output.mTest1.x=index_buffer_componet;
		//output.mTest1.y=index;
	}
	else
	{
		output.mTarget=float4(0.0,0.0,10.0,1.0);
		//debug
		/*float2 debug_position[3];
		debug_position[0]=float2(-1.0,-1.0);
		debug_position[1]=float2(-1.0,1.0);
		debug_position[2]=float2(0.0,0.0);
		output.mTarget.xyz=float3(debug_position[input.mVertexID%3],0.0);*/
	}
}