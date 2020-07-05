#include "stdafx.h"
#include "GameMgr.h"
#include"Block.h"

GameMgr::GameMgr()
{
}

GameMgr::~GameMgr()
{
}

void GameMgr::Init()
{
	m_NumOfPlayer = 1;
}

void GameMgr::Release()
{
}

void GameMgr::CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos)
{
	ObjMgr->AddObject(new Block(num, front, rotation, owner, color, pos), "Block");
}
