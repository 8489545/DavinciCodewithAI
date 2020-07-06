#include "stdafx.h"
#include "GameMgr.h"

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

void GameMgr::BlockInitSetting()
{
	for (int i = 0; i < 13; i++)
	{
		CreateBlock(i, true, 0, 0, Color::BLACK, Vec2(i * 100 + 100, 300));
		CreateBlock(i, true, 0, 0, Color::WHITE, Vec2(i * 100 + 100, 400));
	}
	std::random_device rand;
	std::mt19937 g(rand());

	std::shuffle(m_AllBlock.begin(), m_AllBlock.end(), g);

	int x = 400;
	int y = 1080 / 2 - 100;
	for (auto& iter : m_AllBlock)
	{
		x += 100;
		iter->SetPosition(x, y);

		if (x >= 1400)
		{
			x = 400;
			y += 150;
		}
	}
}

void GameMgr::CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos)
{
	ObjMgr->AddObject(new Block(num, front, rotation, owner, color, pos), "Block");
}
