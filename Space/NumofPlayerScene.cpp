#include "stdafx.h"
#include "NumofPlayerScene.h"

NumofPlayerScene::NumofPlayerScene()
{
}

NumofPlayerScene::~NumofPlayerScene()
{
}

void NumofPlayerScene::Init()
{
	m_BG = Sprite::Create(L"Painting/NumofPlayer/BG.png");
	m_BG->SetPosition(1920 / 2, 1080 / 2);

	m_TwoPlayer = Sprite::Create(L"Painting/NumofPlayer/TwoPlayer.png");
	m_TwoPlayer->SetPosition(1920 / 2, 300);

	m_ThreePlayer = Sprite::Create(L"Painting/NumofPlayer/ThreePlayer.png");
	m_ThreePlayer->SetPosition(1920 / 2, 500);

	m_FourPlayer = Sprite::Create(L"Painting/NumofPlayer/FourPlayer.png");
	m_FourPlayer->SetPosition(1920 / 2, 700);
}

void NumofPlayerScene::Release()
{
}

void NumofPlayerScene::Update(float deltaTime, float Time)
{
}

void NumofPlayerScene::Render()
{
	m_BG->Render();
	m_TwoPlayer->Render();
	m_ThreePlayer->Render();
	m_FourPlayer->Render();
}
