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

	m_JokerPosCompleteButton = Sprite::Create(L"Painting/Game/UI/JokerPosCompleteButton.png");
	m_JokerPosCompleteButton->SetPosition(1600, 900);

	GameMgr::GetInst()->BlockInitSetting();
	GameMgr::GetInst()->SetGamePhase(PHASE::BlockDist);

	TextUIMgr::GetInst()->AddText(72, true, false, "Arial");
	TextUIMgr::GetInst()->AddText(72, true, false, "Arial", Vec2(1920 / 2, 0));


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
	int startingPlayerNum = (rand() % GameMgr::GetInst()->m_NumOfPlayer) + 1;
	GameMgr::GetInst()->m_Turn = startingPlayerNum;

	GameMgr::GetInst()->SetGamePhase(PHASE::BlockFit);
}

void GameScene::BlockFit()
{

}

void GameScene::Update(float deltaTime, float Time)
{
	TextUIMgr::GetInst()->InitText(1, "Player" + std::to_string(GameMgr::GetInst()->m_Turn) + "의 턴");
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::BlockDist)
	{
		TextUIMgr::GetInst()->InitText(0, Vec2(0, 800));
		TextUIMgr::GetInst()->InitText(0, "블럭 선택");
		BlockDist();
	}
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::SetJokerPos)
	{
		TextUIMgr::GetInst()->InitText(0, "조커 위치 지정");
		SetJokerPos();
	}
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::SetOrder)
	{
		TextUIMgr::GetInst()->InitText(0, "순서 정하는중....");
		SetOrder();
	}
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::BlockFit)
	{
		TextUIMgr::GetInst()->InitText(0, "블럭 맞추기");
		BlockFit();
	}
}

void GameScene::Render()
{
	m_BG->Render();
	m_Table->Render();

	if (GameMgr::GetInst()->GetGamePhase() == PHASE::SetJokerPos)
	{
		m_JokerPosCompleteButton->Render();
	}
}
