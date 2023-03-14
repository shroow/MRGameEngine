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
            || UV.x > leftTop.x + atlasSize.x
            || UV.y > leftTop.y + atlasSize.y)
            discard;

        color = atlasTexture.Sample(anisotropicSampler, In.UV);
    }
    else
    {
	    //기존 스프라이트
        color = defaultTexture.Sample(anisotropicSampler, In.UV);
    }

	return color;
}