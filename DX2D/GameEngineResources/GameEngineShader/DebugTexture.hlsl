#include "TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

Output Texture_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    
    return NewOutPut;
}

cbuffer DebugInfo : register(b8)
{
    int4 Type;
    float4 Color;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Texture_PS(Output _Input) : SV_Target0
{
    float4 TexColor = Tex.Sample(Smp, _Input.Tex.xy);
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    return TexColor * Color;
}
