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
	m_NumOfPlayer = 0;
	m_Turn = 1;
	m_Cycle = 1;
}

void GameMgr::Release()
{
}

void GameMgr::Update()
{
	BlockHandSetting();
}

Player* GameMgr::GetPlayer(int num)
{
	return m_Players.at(num);
}

Block* GameMgr::GetRandomBlock()
{
	int num;
	if (m_BlockPile.size() > 0)
	{
		num = (rand() % m_BlockPile.size());
		return m_BlockPile.at(num);
	}
	return nullptr;
}

Block* GameMgr::GetActiveBlock(int num)
{
	if (num == 1)
	{
		for (auto& iter : m_AllBlock)
		{
			if (CollisionMgr::GetInst()->MouseWithBoxSize(iter))
			{
				return iter;
			}
		}
	}
	else if (num == 2)
	{
		for (auto& iter : m_BlockPile)
		{
			if (CollisionMgr::GetInst()->MouseWithBoxSize(iter))
			{
				return iter;
			}
		}
	}
	return nullptr;
}

void GameMgr::PlayerNumSetting(int num)
{
	for (int i = 0; i < num; i++)
	{
		m_Players.push_back(new Player());

		if (i != 0)
			m_Players.at(i)->SetPlayer(i + 1, true);
		else if (i == 0)
			m_Players.at(i)->SetPlayer(i + 1, false);
	}
	m_NumOfPlayer = num;
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
	block->m_Owner = playernum;
	GetPlayer(playernum - 1)->m_Hand.push_back(block);
	m_BlockPile.erase(std::remove(m_BlockPile.begin(), m_BlockPile.end(), block), m_BlockPile.end());
	std::sort(GetPlayer(playernum - 1)->m_Hand.begin(), GetPlayer(playernum - 1)->m_Hand.end(), [](const Block* a, const Block* b)
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
	BlockPileSetting();

	if(GameMgr::GetInst()->GetGamePhase() == PHASE::BlockDist)
		NextTurn();
}
void GameMgr::BlockHandSetting()
{
	int handnum = 0;
	for (int i = 0; i < m_NumOfPlayer; i++)
	{
		Vec2 Pos;
		if (i == 0)
			Pos = Vec2(600, 900);
		else if (i == 1)
			Pos = Vec2(1700, 700);
		for (auto& iter : GetPlayer(i)->m_Hand)
		{
			if (i == 0)
			{
				Pos.x += 100;
			} 
			else if (i == 1)
			{
				iter->m_Rotation = D3DXToRadian(-90);
				Pos.y -= 100;
			}
			iter->m_HandNum = handnum;
			iter->SetPosition(Pos.x, Pos.y);
			
			handnum += 1;
		}
	}
}

void GameMgr::BlockPileSetting()
{
	int x = 400;
	int y = 1080 / 2 - 100;

	for (auto& iter : m_BlockPile)
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

void GameMgr::MoveJoker(int owner)
{
	auto iter = std::find_if(GetPlayer(owner - 1)->m_Hand.begin(), GetPlayer(owner - 1)->m_Hand.end(), [](Block* b)
		{
			if (b->m_BlockNumber == 12 && (b->m_ActiveBlock || b->m_isJokerPositioning))
				return true;
			else
				return false;
		});

	GetPlayer(owner - 1)->m_Hand.erase(std::remove(GetPlayer(owner - 1)->m_Hand.begin(), GetPlayer(owner - 1)->m_Hand.end(), *iter), GetPlayer(owner - 1)->m_Hand.end());

	if (GetPlayer(owner - 1)->m_isAI)
	{
		for (auto& iter : m_AllBlock)
		{
			if (iter->m_Owner == owner && iter->m_BlockNumber == 12 && (iter->m_ActiveBlock || iter->m_isJokerPositioning))
			{
				if (iter->m_HandNum + (_int64)1 > GetPlayer(owner - 1)->m_Hand.size())
				{
					iter->m_HandNum = 0;
				}
				else
				{
					iter->m_HandNum += 1;
				}
				for (auto& iter : GetPlayer(owner - 1)->m_Hand)
				{
					iter->m_HandNum += 1;
				}
				GetPlayer(owner - 1)->m_Hand.insert(GetPlayer(owner - 1)->m_Hand.begin() + iter->m_HandNum, iter);
			}
		}
	}
}

void GameMgr::MoveJoker(int owner, Block* block)
{
	int randPos = rand() % (GetPlayer(owner - 1)->m_Hand.size() + 1);
	if (block->m_Owner == owner && block->m_BlockNumber == 12 && block->m_isJokerPositioning && !block->m_isJokerAlreadyMoved)
	{
		for (auto& iter : GetPlayer(owner - 1)->m_Hand)
		{
			if (iter->m_HandNum >= randPos || iter->m_HandNum < block->m_HandNum)
			{
				iter->m_HandNum += 1;
			}
		}
		block->m_HandNum = randPos;
		GetPlayer(owner - 1)->m_Hand.insert(GetPlayer(owner - 1)->m_Hand.begin() + block->m_HandNum, block);
	}
}

void GameMgr::NextTurn()
{
	if (m_Turn == m_NumOfPlayer)
	{
		m_Turn = 1;
		m_Cycle += 1;
	}
	else
		m_Turn += 1;
}
