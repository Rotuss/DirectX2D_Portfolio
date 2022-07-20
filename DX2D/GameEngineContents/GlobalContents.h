#pragma once
#include "Player.h"
#include "Monster.h"

enum class OBJECTORDER
{
	Player,
	Monster,
};

// Ό³Έν :
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
	GlobalContents();
	~GlobalContents();
};

