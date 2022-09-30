#include "TransformHeader.fx"
#include "RenderOption.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
    
    uint Index : ROWINDEX;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
    //float4 Tex1 : TEXCOORD1;
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
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    // 애니메이션용
    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    // 마스크 이용을 위한 텍스쳐 그 자체를 받는 코드
    //NewOutPut.Tex1 = _Input.Tex;
    
    return NewOutPut;
}

Output TextureAtlas_VSINST(Input _Input)
{
    Output NewOutPut = (Output) 0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
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
//Texture2D Mask : register(t1);
SamplerState Smp : register(s0);

float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    //float4 MaskColor = Mask.Sample(Smp, _Input.Tex1.xy);
    float4 RenderColor = (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    
    // 마스크 컬러별 clip
    //if(1 == MaskColor.r)
    //{
    //    clip(-1);
    //}
    
    // 렌더옵션을 이용하여 마스크 설정시 clip    
    //if(1 == IsMask)
    //{
    //    clip(-1);
    //}
    
    if (_Input.Tex.x < Slice.x)
    {
        clip(-1);
    }
    
    if (_Input.Tex.y < Slice.y)
    {
        clip(-1);
    }
    
    float4 TexColor = Tex.Sample(Smp, _Input.Tex.xy);
    
    if (TexColor.a == 0)
    {
        clip(-1);
    }
    
    if (1 == IsOldFilmColor)
    {
        float4 OldFilmColor = (float4(1.0f - TexColor.rgb, 1.0f) * MulColor) + PlusColor;

        return OldFilmColor;
    }
    
    return RenderColor;
}