#include "PreCompile.h"
#include "GameEngineDebug.h"
#include <iostream>

HANDLE GameEngineDebug::hConsole = nullptr;

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

void GameEngineDebug::ConsoleOpen()
{
	if (AllocConsole())
	{
		FILE* FIle;
		freopen_s(&FIle, "CONIN$", "rb", stdin);
		freopen_s(&FIle, "CONOUT$", "wb", stdout);
		freopen_s(&FIle, "CONOUT$", "wb", stderr);

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout << "Console Start" << std::endl;
	}
}

void GameEngineDebug::OutPutString(const std::string& _Text)
{
	// #ifdef _DEBUG
	OutputDebugStringA((_Text + "\n").c_str());
	// #endif
}

void GameEngineDebug::Destroy()
{
	if (nullptr != hConsole)
	{
		FreeConsole();
	}
}

GameEngineDebug::GameEngineDebug()
{
}

GameEngineDebug::~GameEngineDebug() 
{
}

