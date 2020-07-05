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

	GameMgr::GetInst()->CreateBlock(10, true, 0, 1, Color::WHITE, Vec2(100, 100));
	GameMgr::GetInst()->CreateBlock(12, false, 0, 1, Color::WHITE, Vec2(200, 100));
	GameMgr::GetInst()->CreateBlock(4, true, 0, 1, Color::BLACK, Vec2(300, 100));
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
