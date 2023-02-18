#include "globals.hlsli"

float4 main(VSOut In) : SV_Target
{
	float4 color = (float)0.f;
	
	color = defaultTexture.Sample(anisotropicSampler, In.UV);

	return color;
}