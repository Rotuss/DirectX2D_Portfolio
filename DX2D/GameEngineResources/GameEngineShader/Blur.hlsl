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


Output Blur_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}


static float Gau[5][5] =
{
    { 01, 04, 06, 04, 01 },
    { 04, 16, 24, 16, 04 },
    { 06, 24, 36, 24, 06 },
    { 04, 16, 24, 16, 04 },
    { 01, 04, 06, 04, 01 }
};

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 Blur_PS(Output _Input) : SV_Target0
{
    float2 PixelUVSize = float2(1.0f / 1280.0f, 1.0f / 720.0f);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    float2 CurUV = StartUV;
    
    float4 Result = (float4) 0.0f;
    
    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            Result += Tex.Sample(Smp, CurUV) * Gau[y][x];
            CurUV.x += PixelUVSize.x;
        }
        
        CurUV.x = StartUV.x;
        CurUV.y += PixelUVSize.y;
    }
    
    Result /= 256.0f;
    
    if (Result.a <= 0.0f)
    {
        clip(-1);
    }
    
    if (1.0f <= Result.a)
    {
        Result.a = 1.0f;
    }
    
    return Result;
}
