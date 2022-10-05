#pragma once
#include "Player.h"
#include "Monster.h"
#include "MsChalice.h"

enum class OBJECTORDER
{
	Title,
	World,
	Tutorial,
	WorldSnow,
	Player,
	Monster,
	Boss,
	BossMinion,
	BossWhale,
	SnowPlatform,
	Weapon,
	Parry,
	Phase3Bot,
	UI = 1000,
};

// Ό³Έν :
class GlobalContents
{
public:
	class Actors
	{
	public:
		static Monster* TestMonster;
		static bool IsClear;

	private:
		Actors() {		}
		~Actors() {		}
	};

protected:

private:
	// constrcuter destructer
	GlobalContents() {}
	~GlobalContents() {}
};

