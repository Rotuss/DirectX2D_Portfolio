#pragma once
#include "Player.h"
#include "Monster.h"

enum class OBJECTORDER
{
	Title,
	World,
	Tutorial,
	Player,
	Monster,
	Boss,
	UI = 1000,
};

// ���� :
class GlobalContents
{
public:
	class Actors
	{
	public:
		static Monster* TestMonster;

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

