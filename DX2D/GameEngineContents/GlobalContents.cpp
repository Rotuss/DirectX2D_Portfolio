#include "PreCompile.h"
#include "GlobalContents.h"

GameEngineSoundPlayer GlobalContents::Actors::BGM;
Monster* GlobalContents::Actors::TestMonster = nullptr;
float GlobalContents::Actors::TimeOverCheck = 0.0f;
bool GlobalContents::Actors::IsTimeOver = false;
bool GlobalContents::Actors::IsClear = false;