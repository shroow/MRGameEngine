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

//cbuffer time
//int 0
//시간을 받아와서 시간에 증가에 따라 색상에 값 변경 해주기
//ex: color.a += time;

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.f;
	
    color = defaultTexture.Sample(anisotropicSampler, In.UV);
    
    float fAlpha = alpha;
    
    color.a += fAlpha;
    
    return float4(color.r, color.g, color.b, color.a);
}