#pragma once
#include "Player.h"
#include "Monster.h"

enum class OBJECTORDER
{
	Player,
	Monster,
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
	GlobalContents();
	~GlobalContents();
};

