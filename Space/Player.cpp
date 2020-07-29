#include "stdafx.h"
#include "Player.h"
#include"BlockFitPanel.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetPlayer(int num, bool ai)
{
	m_PlayerNum = num;
	m_isAI = ai;
	m_isFittingBlock = false;
}


void Player::BlockDist()
{
	if (GameMgr::GetInst()->m_Turn == m_PlayerNum)
	{
		GameMgr::GetInst()->BlockInHand(m_PlayerNum, GameMgr::GetInst()->GetRandomBlockExcludingJoker());
	}
}

void Player::BlockInHand()
{
	if (GameMgr::GetInst()->m_Turn == m_PlayerNum)
	{
		if (m_isAI)
			GameMgr::GetInst()->BlockInHand(m_PlayerNum, GameMgr::GetInst()->GetRandomBlock());
		else
		{
			if (INPUT->GetButtonDown() && GameMgr::GetInst()->GetActiveBlock(BLOCKPILE) != nullptr)
			{
				INPUT->ButtonDown(false);
				GameMgr::GetInst()->BlockInHand(m_PlayerNum, GameMgr::GetInst()->GetActiveBlock(BLOCKPILE));
			}
		}
	}
}

void Player::MoveJoker()
{
	for (auto& iter : m_Hand)
	{
		if (!m_isAI)
		{
			if (iter->m_BlockNumber == 12 && iter->m_ActiveBlock == true && !iter->m_isJokerAlreadyMoved && !iter->m_isRevealedBlock)
			{
				if (INPUT->GetButtonDown())
				{
					INPUT->ButtonDown(false);
					GameMgr::GetInst()->MoveJoker(m_PlayerNum);
				}
			}
		}
		else
		{
			if (iter->m_BlockNumber == 12 && !iter->m_isJokerAlreadyMoved && !iter->m_isRevealedBlock)
			{
				iter->m_isJokerAlreadyMoved = true;
				GameMgr::GetInst()->MoveJoker(m_PlayerNum, iter);
			}
		}
	}
}

void Player::BlockFit()
{
	for (auto& iter : GameMgr::GetInst()->m_AllBlock)
	{
		if (!m_isAI)
		{
			if ((iter->m_Owner != m_PlayerNum && iter->m_Owner != 0) && iter->m_ActiveBlock && INPUT->GetButtonDown())
			{
				m_isFittingBlock = true;
				ObjMgr->AddObject(new BlockFitPanel(iter, m_PlayerNum), "UI");
			}
		}
		else
		{
			BlockPrediction();
		}
	}
}

void Player::BlockFitSuccess()
{
	GameMgr::GetInst()->SetGamePhase(PHASE::SelectNextAct);
}

void Player::BlockFitFailed()
{
	m_PrevBlock->m_Front = true;
	m_PrevBlock->m_isRevealedBlock = true;

	GameMgr::GetInst()->NextTurn();
	GameMgr::GetInst()->SetGamePhase(PHASE::ImportBlock);
}

void Player::BlockPrediction()
{
	for(auto& i : GameMgr::GetInst()->m_Players)
	{
		if (i->m_PlayerNum != m_PlayerNum)
		{
			int iterpos = 1;

			int BlackMin = 13;
			int BlackMax = -1;
			int WhiteMin = 13;
			int WhiteMax = -1;
			for (const auto& iter : GameMgr::GetInst()->GetPlayer(i->m_PlayerNum - 1)->m_Hand)
			{


				iterpos++;
			}
		}
	}
}

bool Player::BlockCompare()
{
	return false;
}

void Player::ProbabilityCaculation()
{
}

void Player::Update(float deltaTime, float Time)
{
	for (auto& iter : m_Hand)
	{
		if (!m_isAI)
		{
			if (iter->m_isRevealedBlock)
			{
				iter->SetScale(0.75, 0.75);
			}
		}
	}
}

void Player::Render()
{
}
