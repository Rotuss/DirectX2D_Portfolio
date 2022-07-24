#include "TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 Pos2 : POSITION;
    float4 Color : COLOR;
};

Output Color_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.Pos = mul(NewOutPut.Pos, WorldViewProjection);
    
    NewOutPut.Pos2 = _Input.Pos;
    
    NewOutPut.Color = _Input.Color;
    
    return NewOutPut;
}

float4 Color_PS(Output _Input) : SV_Target0
{
    float Len = length(_Input.Pos2.xy);
    
        if (Len >= 0.5f)
    {
        return float4(1.0f, 0.0f, 1.0f, 1.0f);
    }
    
    return _Input.Color;
}