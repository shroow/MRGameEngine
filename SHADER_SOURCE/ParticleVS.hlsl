#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    uint iInstance : SV_InstanceID; //자동생성되면 번호를 매겨줌
};

struct VSOut
{
    float4 Pos : SV_POSITION;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;

    float3 worldPos = (In.Pos.xyz * 5.0f) + world._41_42_43 +
                    particleBuffer[In.iInstance].position.xyz;
    
    float4 viewPos = mul(float4(worldPos, 1.0f), view);
    Out.Pos = mul(viewPos, projection);

	return Out;
}