#include "GameEngineMath.h"

GameEngineMath::GameEngineMath() 
{
}

GameEngineMath::~GameEngineMath() 
{
}

const float GameEngineMath::PI = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PI2 = PI * 2.0f;
const float GameEngineMath::DEG = 180.0f;

//                                          3.14 / 180.0f
const float GameEngineMath::DegreeToRadian = PI / DEG;
//										   180.0f / 3.14 
const float GameEngineMath::RadianToDegree = DEG / PI;


const float4 float4::LEFT = { -1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::RIGHT = { 1.0f, 0.0f, 0.0f, 1.0f };;
const float4 float4::UP = { 0.0f, -1.0f, 0.0f, 1.0f };;
const float4 float4::DOWN = { 0.0f, 1.0f, 0.0f, 1.0f };;
const float4 float4::ZERO = { 0.0f, 0.0f, 0.0f, 0.0f };;
const float4 float4::ONE = { 1.0f, 1.0f, 1.0f, 1.0f };