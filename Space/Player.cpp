#include "stdafx.h"
#include "Player.h"

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
			/*if (iter->m_BlockNumber == 12 && iter->m_ActiveBlock == true)
			{
				if (INPUT->GetButtonDown())
				{
					INPUT->ButtonDown(false);
					GameMgr::GetInst()->MoveJoker(m_PlayerNum);
				}
			}*/

			if (iter->m_BlockNumber == 12 && !iter->m_isJokerAlreadyMoved)
			{
				iter->m_isJokerPositioning = true;
				GameMgr::GetInst()->MoveJoker(m_PlayerNum);
				iter->m_isJokerAlreadyMoved = true;
			}
		}
		else
		{
		}
	}
}

void Player::Update(float deltaTime, float Time)
{
}

void Player::Render()
{
}
