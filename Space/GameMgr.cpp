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

Block* GameMgr::GetRandomBlockExcludingJoker()
{
	int num;
	if (m_BlockPile.size() > 0)
	{
		while (1)
		{
			num = (rand() % m_BlockPile.size());

			if (m_BlockPile.at(num)->m_BlockNumber == 12)
			{
				num = (rand() % m_BlockPile.size());
			}
			if (m_BlockPile.at(num)->m_BlockNumber != 12)
				return m_BlockPile.at(num);
		}
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
		CreateBlock(i, false, 0, 0, Color::BLACK, Vec2(i * 100 + 100, 300));
		CreateBlock(i, false, 0, 0, Color::WHITE, Vec2(i * 100 + 100, 400));
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

void GameMgr::BlockInHand(int playernum, Block* block)
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
			return false;
		});
	BlockPileSetting();

	GetPlayer(playernum - 1)->m_PrevBlock = block;

	if (playernum == 1)
	{
		block->m_Front = true;
	}

	if (GameMgr::GetInst()->GetGamePhase() == PHASE::BlockDist)
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
		{
			if (m_NumOfPlayer == 2)
				Pos = Vec2(600, 200);
			else
				Pos = Vec2(1700, 1000);
		}
		for (auto& iter : GetPlayer(i)->m_Hand)
		{
			if (i == 0)
			{
				Pos.x += 100;
			}
			else if (i == 1)
			{
				if (m_NumOfPlayer == 2)
				{
					iter->m_Rotation = D3DXToRadian(-180);
					Pos.x += 100;
				}
				else
				{
					iter->m_Rotation = D3DXToRadian(-90);
					Pos.y -= 100;
				}
			}
			iter->m_HandNum = handnum;
			iter->SetPosition(Pos.x, Pos.y);

			handnum += 1;
		}
	}
}

void GameMgr::BlockPileSetting()
{
	int x = 500;
	int y = 1080 / 2 - 100;

	for (auto& iter : m_BlockPile)
	{
		x += 100;
		iter->SetPosition(x, y);

		if (x >= 1300)
		{
			x = 500;
			y += 150;
		}
	}
}

void GameMgr::MoveJoker(int owner)
{
	auto iter = std::find_if(GetPlayer(owner - 1)->m_Hand.begin(), GetPlayer(owner - 1)->m_Hand.end(), [](Block* b)
		{
			if (b->m_BlockNumber == 12 && b->m_ActiveBlock)
				return true;
			else
				return false;
		});

	GetPlayer(owner - 1)->m_Hand.erase(std::remove(GetPlayer(owner - 1)->m_Hand.begin(), GetPlayer(owner - 1)->m_Hand.end(), *iter), GetPlayer(owner - 1)->m_Hand.end());

	for (auto& iter : m_AllBlock)
	{
		if (iter->m_Owner == owner && iter->m_BlockNumber == 12 && iter->m_ActiveBlock)
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

void GameMgr::MoveJoker(int owner, Block* block)
{
	int randPos = rand() % (GetPlayer(owner - 1)->m_Hand.size() + 1);
	block->m_HandNum = randPos;

	auto iter = std::find_if(GetPlayer(owner - 1)->m_Hand.begin(), GetPlayer(owner - 1)->m_Hand.end(), [block](Block* b)
		{
			if (b == block)
				return true;
			else
				return false;
		});

	GetPlayer(owner - 1)->m_Hand.erase(std::remove(GetPlayer(owner - 1)->m_Hand.begin(), GetPlayer(owner - 1)->m_Hand.end(), *iter), GetPlayer(owner - 1)->m_Hand.end());

	for (auto& iter : GameMgr::GetInst()->GetPlayer(owner - 1)->m_Hand)
	{
		if (randPos <= iter->m_HandNum)
			iter->m_HandNum += 1;

		if (iter->m_HandNum >= GameMgr::GetInst()->GetPlayer(owner - 1)->m_Hand.size())
			iter->m_HandNum = GameMgr::GetInst()->GetPlayer(owner - 1)->m_Hand.size();
	}
	GetPlayer(owner - 1)->m_Hand.insert(GetPlayer(owner - 1)->m_Hand.begin() + block->m_HandNum, block);
}

void GameMgr::BlockFit(int owner)
{
	if (GetPlayer(owner - 1)->m_isFittingBlock == false)
	{ 
		GetPlayer(owner - 1)->BlockFit();
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
