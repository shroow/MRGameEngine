#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_POSITION;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_TARGET
{
	float4 color = (float)0.f;
	
    if(animationType == 1) //2D
    {
        float2 diff = (atlasSize - spriteSize) / 2.0f;
        
        float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
        if (UV.x < leftTop.x || UV.y < leftTop.y 
            || UV.x > leftTop.x + spriteSize.x 
            || UV.y > leftTop.y + spriteSize.y)
            discard;
        
        color = atlasTexture.Sample(anisotropicSampler, UV);
    }
    else
    {
	    //기존 스프라이트
        color = defaultTexture.Sample(anisotropicSampler, In.UV);
    }

    LightColor lightColor = (LightColor)0.0f;
    for (uint i = 0; i < numberOfLight; i++)
    {
        CalculateLight(lightColor, In.WorldPos.xyz, i);
    }

    //if (numberOfLight <= 0)
    //{
    //    lightColor = (LightColor) 1.0f;
    //}

    color *= lightColor.diffuse;
    //color = defaultTexture.Sample(anisotropicSampler, In.UV);

	return color;
}