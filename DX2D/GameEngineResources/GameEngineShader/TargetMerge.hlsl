struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;
};

Output TargetMerge_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    
    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 TargetMerge_PS(Output _Input) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _Input.Tex.xy);
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    if (Color.a >= 1.0f)
    {
        Color.a = 1.0f;
    }
    
    return Color;
}
