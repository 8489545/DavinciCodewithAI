#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	m_BG = Sprite::Create(L"Painting/Game/BG.png");
	m_BG->SetPosition(1920 / 2, 1080 / 2);
	m_Table = Sprite::Create(L"Painting/Game/Table.png");
	m_Table->SetPosition(1920 / 2, 1080 / 2);

	m_UIBlockDist = Sprite::Create(L"Painting/Game/UI/Dist.png");
	m_UIBlockDist->SetPosition(1920 / 2, 100);
	m_UISetJokerPos = Sprite::Create(L"Painting/Game/UI/JokerPos.png");
	m_UISetJokerPos->SetPosition(1920 / 2, 100);
	m_JokerPosCompleteButton = Sprite::Create(L"Painting/Game/UI/JokerPosCompleteButton.png");
	m_JokerPosCompleteButton->SetPosition(1600, 900);

	GameMgr::GetInst()->BlockInitSetting();
	GameMgr::GetInst()->SetGamePhase(PHASE::BlockDist);

	m_DistBlockNum = 0;
}

void GameScene::Release()
{
}

void GameScene::BlockDist()
{
	if (GameMgr::GetInst()->m_BlockPile.size() > 0)
	{
		if ((GameMgr::GetInst()->m_NumOfPlayer == 2 || GameMgr::GetInst()->m_NumOfPlayer == 3))
		{
			auto& iter = GameMgr::GetInst()->m_Players.at(GameMgr::GetInst()->m_NumOfPlayer - (_int64)1);
			if (iter->m_Hand.size() < 4)
			{
				for (auto& iter : GameMgr::GetInst()->m_Players)
				{
					iter->BlockInHand();
				}
			}
			else
			{
				GameMgr::GetInst()->SetGamePhase(PHASE::SetJokerPos);
			}
		}
	}
}

void GameScene::SetJokerPos()
{
	for (auto& iter : GameMgr::GetInst()->m_Players)
	{
		iter->MoveJoker();
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_JokerPosCompleteButton) && INPUT->GetButtonDown())
	{
		for (auto& iter : GameMgr::GetInst()->m_AllBlock)
			iter->m_isJokerPositioning = false;

		GameMgr::GetInst()->SetGamePhase(PHASE::SetOrder);
	}
}

void GameScene::SetOrder()
{
}

void GameScene::BlockFit()
{

}

void GameScene::Update(float deltaTime, float Time)
{
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::BlockDist)
	{
		BlockDist();
	}
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::SetJokerPos)
	{
		SetJokerPos();
	}
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::SetOrder)
	{
		SetOrder();
	}
}

void GameScene::Render()
{
	m_BG->Render();
	m_Table->Render();
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::BlockDist)
		m_UIBlockDist->Render();

	if (GameMgr::GetInst()->GetGamePhase() == PHASE::SetJokerPos)
	{
		m_UISetJokerPos->Render();
		m_JokerPosCompleteButton->Render();
	}
}
