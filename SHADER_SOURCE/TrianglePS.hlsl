

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

cbuffer Transform : register(b0)
{
    float4 cb_Pos;
}

cbuffer MaterialData : register(b1)
{
    int cb_iData;
    float cb_fData;
    float2 cb_xy;
    float3 cb_xyz;
    float4 cb_xyzw;
    matrix cb_mat;
}

Texture2D defaultTexture : register(t0);

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

float4 PS_Test(VTX_OUT _in) : SV_Target
{
    float4 color = (float) 0.0f;
    
    color = defaultTexture.Sample(anisotropicSampler, _in.vUV);
    
    return color;
}