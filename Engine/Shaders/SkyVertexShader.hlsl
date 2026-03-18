#include "ShaderCommon.hlsli"

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	float4 WorldPos = mul(float4(Input.Position, 1.0f), World);
	float4 ViewPos = mul(WorldPos, View);
	float4 ClipPos = mul(ViewPos, Projection);
	Output.Color = Input.Color;
	Output.Normal = mul(Input.Normal, (float3x3) World);
	return Output;

 //   // ★ Sky를 항상 Far Plane에 고정 (z = w → NDC depth = 1.0)
 //   // 다른 오브젝트가 항상 앞에 그려짐
	//ClipPos.z = ClipPos.w;

	//Output.Position = ClipPos;
	//Output.Color = Input.Color;
	//Output.Normal = mul(Input.Normal, (float3x3) World);
	//return Output;
}
