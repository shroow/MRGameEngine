#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
    
    float2 WorldPos : POSITION;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 Out = float4(1.f, 1.f, 1.f, 1.f);
    
    const float Width = 100;
    const float Height = 100;
    
    int worldX = (int) In.WorldPos.x;
    int worldY = (int) In.WorldPos.y;
    
    const float Tickness = 1.0f;
    
    if (abs((worldX + 1) % Width) <= Tickness)
        return Out;    
        
    if (abs((worldY + 1) % Height) <= Tickness)
        return Out;
    
    discard;
    return float4(1.f, 1.f, 1.f, 1.f);
}
