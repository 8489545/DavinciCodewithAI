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

	m_KeepFitButton = Sprite::Create(L"Painting/Game/UI/KeepFitButton.png");
	m_KeepFitButton->SetPosition(150, 900);

	m_StopFitButton = Sprite::Create(L"Painting/Game/UI/StopFitButton.png");
	m_StopFitButton->SetPosition(400, 900);

	GameMgr::GetInst()->BlockInitSetting();
	GameMgr::GetInst()->SetGamePhase(PHASE::BlockDist);

	TextUIMgr::GetInst()->AddText(72, true, false, "Arial");
	TextUIMgr::GetInst()->AddText(72, true, false, "Arial", Vec2(1920 / 2, 0));
	TextUIMgr::GetInst()->AddText(48, true, false, "Arial", Vec2(1920 / 2, 72));


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
					iter->BlockDist();
				}
			}
			else
			{
				GameMgr::GetInst()->SetGamePhase(PHASE::SetOrder);
			}
		}
	}
}

void GameScene::SetOrder()
{
	int startingPlayerNum = (rand() % GameMgr::GetInst()->m_NumOfPlayer) + 1;
	GameMgr::GetInst()->m_Turn = startingPlayerNum; 
	GameMgr::GetInst()->m_Cycle = 1;
	GameMgr::GetInst()->SetGamePhase(PHASE::ImportBlock);
}

void GameScene::ImportBlock()
{
	for (auto& iter : GameMgr::GetInst()->m_Players)
	{
		iter->BlockInHand();

		int InitialHand = 0;
		if (GameMgr::GetInst()->m_NumOfPlayer == 2 || GameMgr::GetInst()->m_NumOfPlayer == 3)
			InitialHand = 4;
		else if (GameMgr::GetInst()->m_NumOfPlayer == 4)
			InitialHand = 3;
		
		if (iter->m_Hand.size() == InitialHand + GameMgr::GetInst()->m_Cycle)
		{
			for (auto& iter2 : iter->m_Hand)
			{
				if (iter2->m_BlockNumber == 12 && !iter2->m_isJokerAlreadyMoved)
				{
					if (!iter->m_isAI)
					{
						GameMgr::GetInst()->SetGamePhase(PHASE::MoveJokerPos);
						return;
					}
					else if (iter->m_isAI)
					{
						iter->MoveJoker();
					}
				}
				
			}
			iter->SetVisbleHand();
			GameMgr::GetInst()->SetGamePhase(PHASE::BlockFit);
		}
	}
}

void GameScene::MoveJokerPos()
{
	for (auto& iter : GameMgr::GetInst()->m_Players)
	{
		iter->MoveJoker();
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_JokerPosCompleteButton) && INPUT->GetButtonDown())
	{
		for (auto& iter : GameMgr::GetInst()->m_Players)
		{
			for (auto& iter2 : iter->m_Hand)
			{
				if (iter2->m_BlockNumber == 12)
					iter2->m_isJokerAlreadyMoved = true;
			}
		}
		GameMgr::GetInst()->SetGamePhase(PHASE::BlockFit);
	}
}

void GameScene::BlockFit()
{
	GameMgr::GetInst()->BlockFit(GameMgr::GetInst()->m_Turn);
}

void GameScene::NextAction()
{
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_KeepFitButton) && INPUT->GetButtonDown())
	{
		INPUT->ButtonDown(false);
		GameMgr::GetInst()->SetGamePhase(PHASE::BlockFit);
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_StopFitButton) && INPUT->GetButtonDown())
	{
		INPUT->ButtonDown(false);
		GameMgr::GetInst()->NextTurn();
		GameMgr::GetInst()->SetGamePhase(PHASE::ImportBlock);
	}
}

void GameScene::Update(float deltaTime, float Time)
{
	TextUIMgr::GetInst()->InitText(TURNUI, "Player" + std::to_string(GameMgr::GetInst()->m_Turn) + "의 턴");

	switch (GameMgr::GetInst()->GetGamePhase())
	{
	case PHASE::BlockDist:
		TextUIMgr::GetInst()->InitText(PHASEUI, Vec2(0, 0));
		TextUIMgr::GetInst()->InitText(PHASEUI, "블럭 선택");
		BlockDist();
		break;
	case PHASE::SetOrder:
		TextUIMgr::GetInst()->InitText(PHASEUI, "순서 정하는중....");
		SetOrder();
		break;
	case PHASE::ImportBlock:
		TextUIMgr::GetInst()->InitText(PHASEUI, "블럭 가져오기");
		ImportBlock();
		break;
	case PHASE::MoveJokerPos:
		TextUIMgr::GetInst()->InitText(PHASEUI, "조커 위치 정하기");
		MoveJokerPos();
		break;
	case PHASE::BlockFit:
		TextUIMgr::GetInst()->InitText(PHASEUI, "블럭 맞추기");
		BlockFit();
		break;
	case PHASE::SelectNextAct:
		TextUIMgr::GetInst()->InitText(PHASEUI, "다음 행동 선택");
		NextAction();
		break;
	case PHASE::NONE:
		break;
	default:
		break;
	}
}

void GameScene::Render()
{
	m_BG->Render();
	m_Table->Render();

	if (GameMgr::GetInst()->GetGamePhase() == PHASE::MoveJokerPos)
	{
		m_JokerPosCompleteButton->Render();
	}
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::SelectNextAct)
	{
		m_KeepFitButton->Render();
		m_StopFitButton->Render();
	}
}
