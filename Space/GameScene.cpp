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

	GameMgr::GetInst()->BlockInitSetting();
}

void GameScene::Release()
{
}

void GameScene::Update(float deltaTime, float Time)
{
}

void GameScene::Render()
{
	m_BG->Render();
	m_Table->Render();
}
