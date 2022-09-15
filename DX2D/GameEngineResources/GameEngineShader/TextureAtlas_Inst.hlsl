#include "TransformHeader.fx"
#include "RenderOption.fx"

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

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    
    float4 PivotPos;
};

Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.Pos = mul(_Input.Pos, AllTransformData[0].WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    return NewOutPut;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    float4 RenderColor = (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    
    if (_Input.Tex.x < Slice.x)
    {
        clip(-1);
    }
    
    float4 TexColor = Tex.Sample(Smp, _Input.Tex.xy);
    
    if (TexColor.a == 0)
    {
        clip(-1);
    }

    return RenderColor;
}
