#pragma once
#include <GameEngineCore/GameEngineRenderSet.h>
#include<GameEngineCore/GameEngineRenderTarget.h>

// Ό³Έν :
class OldFilm : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	OldFilm();
	~OldFilm();

	// delete Function
	OldFilm(const OldFilm& _Other) = delete;
	OldFilm(OldFilm&& _Other) noexcept = delete;
	OldFilm& operator=(const OldFilm& _Other) = delete;
	OldFilm& operator=(OldFilm&& _Other) noexcept = delete;

	virtual void EffectInit();
	virtual void Effect(GameEngineRenderTarget* _Target);

protected:
	GameEngineRenderTarget* CopyTarget;
	GameEngineRenderSet EffectSet;

private:

};

