#pragma once

#include <string>

#include <set>
#include <map>
#include <list>
#include <vector>
#include <chrono>

#include <Windows.h>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#include <DirectXCollision.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

// base
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineInput.h>

// core
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

#include "GlobalContents.h"