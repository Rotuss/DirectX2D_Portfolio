cbuffer TransformData : register(b0)
{
    float4 LocalPosition;
    float4 LocalRotation;
    float4 LocalScaling;
    
    float4 WorldPosition;
    float4 WorldRotation;
    float4 WorldScaling;
    
    float4x4 LocalPositionMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalScalingMatrix;
    
    float4x4 LocalWorldMatrix;
    float4x4 WorldWorldMatrix;
    float4x4 View;
    float4x4 Projection;
    
    float4x4 WorldView;
    float4x4 WorldViewProjection;
};

struct Input
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

Output Color_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Color = _Input.Color;
    
    return NewOutPut;
}

float4 Color_PS(Output _Input) : SV_Target0
{
    return _Input.Color;
}