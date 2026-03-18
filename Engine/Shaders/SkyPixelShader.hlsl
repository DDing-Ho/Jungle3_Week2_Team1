#include "ShaderCommon.hlsli"

cbuffer SkyData : register(b2)
{
	float4 SkyColor; 
	float4 HorizonColor; 
	float4 GroundColor; 
};

float4 main(VS_OUTPUT Input) : SV_TARGET
{

	float Tangent = Input.Normal.z; 

	float4 Color;
	if (Tangent > 0.0f)
		Color = lerp(HorizonColor, SkyColor, Tangent);
	else
		Color = lerp(HorizonColor, GroundColor, -Tangent);

	return float4(Color.rgb, 1.0f);
}
