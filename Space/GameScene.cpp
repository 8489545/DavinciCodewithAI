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

	GameMgr::GetInst()->BlockInitSetting();
	GameMgr::GetInst()->SetGamePhase(PHASE::BlockDist);
}

void GameScene::Release()
{
}

void GameScene::BlockDist()
{
}

void GameScene::Update(float deltaTime, float Time)
{
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::BlockDist)
	{
		BlockDist();
	}
}

void GameScene::Render()
{
	m_BG->Render();
	m_Table->Render();
	if (GameMgr::GetInst()->GetGamePhase() == PHASE::BlockDist)
		m_UIBlockDist->Render();
}
