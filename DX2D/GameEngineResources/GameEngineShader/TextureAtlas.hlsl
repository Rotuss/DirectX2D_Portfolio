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
    //float4 Tex1 : TEXCOORD1;
};

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
};

Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos.w = 1.0f;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    // �ִϸ��̼ǿ�
    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    // ����ũ �̿��� ���� �ؽ��� �� ��ü�� �޴� �ڵ�
    //NewOutPut.Tex1 = _Input.Tex;
    
    return NewOutPut;
}

cbuffer ColorData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
}

Texture2D Tex : register(t0);
//Texture2D Mask : register(t1);
SamplerState Smp : register(s0);

float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    //float4 MaskColor = Mask.Sample(Smp, _Input.Tex1.xy);
    float4 RenderColor = (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    
    // ����ũ �÷��� clip
    //if(1 == MaskColor.r)
    //{
    //    clip(-1);
    //}
    
    // �����ɼ��� �̿��Ͽ� ����ũ ������ clip    
    //if(1 == IsMask)
    //{
    //    clip(-1);
    //}
    
    return RenderColor;
}