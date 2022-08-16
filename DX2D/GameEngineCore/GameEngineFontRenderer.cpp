#include "PreCompile.h"
#include "GameEngineFontRenderer.h"

GameEngineRenderTarget* GameEngineFontRenderer::FontTarget = nullptr;

GameEngineFontRenderer::GameEngineFontRenderer() 
	: Font(nullptr)
	, Color(float4::WHITE)
	, ScreenPosition(float4::ZERO)
	, FontSize(20.0f)
{
}

GameEngineFontRenderer::~GameEngineFontRenderer() 
{
}

void GameEngineFontRenderer::SetText(const std::string& _Text, const std::string& _Font)
{
	Text = _Text;
	Font = GameEngineFont::Find(_Font);
}

void GameEngineFontRenderer::Start()
{
	/*if (nullptr == FontTarget)
	{
		FontTarget = GameEngineRenderTarget::Create("FontTarget");
		FontTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), float4::ZERO);
	}*/
	
	PushRendererToMainCamera();
}

void GameEngineFontRenderer::Render(float _DeltaTime)
{
	if (nullptr == Font)
	{
		return;
	}

	Font->FontDraw(Text, FontSize, ScreenPosition, Color, static_cast<int>(LR) | static_cast<int>(TB));
	GameEngineRenderingPipeLine::AllShaderReset();
}
