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

void GameMgr::Update()
{
	
	if(m_Player1Hand.size() > 0)
		BlockHandSetting();
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
	m_BlockPile.assign(m_AllBlock.begin(), m_AllBlock.end());
}

void GameMgr::CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos)
{
	ObjMgr->AddObject(new Block(num, front, rotation, owner, color, pos), "Block");
}

void GameMgr::BlockInHand(int playernum,Block* block)
{
	switch (playernum)
	{
	case 1:
		m_Player1Hand.push_back(block);
		std::sort(m_Player1Hand.begin(), m_Player1Hand.end(), [](const Block* a, const Block* b) 
			{
				if (a->m_BlockNumber == b->m_BlockNumber)
				{
					if (b->m_Color == Color::BLACK)
						return a->m_BlockNumber < b->m_BlockNumber;
				}
				else
				{
					return a->m_BlockNumber < b->m_BlockNumber;
				}
			});
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

void GameMgr::BlockHandSetting()
{
	Vec2 Pos = Vec2(600, 900);
	for (auto& iter : m_Player1Hand)
	{
		Pos.x += 100;
		iter->SetPosition(Pos.x, Pos.y);
	}
}
