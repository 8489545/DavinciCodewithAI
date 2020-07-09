#include "stdafx.h"
#include "NumofPlayerScene.h"
#include"GameScene.h"

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

	m_EnterButton = Sprite::Create(L"Painting/NumofPlayer/Enter.png");
	m_EnterButton->SetPosition(1700, 900);

	m_NumOfPlayer = 0;
	INPUT->ButtonDown(false);
}

void NumofPlayerScene::Release()
{
}

void NumofPlayerScene::Update(float deltaTime, float Time)
{
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_TwoPlayer))
	{
		m_TwoPlayer->B = 0;
		if (INPUT->GetButtonDown())
			m_NumOfPlayer = 2;
	}
	else
	{
		if (m_NumOfPlayer != 2)
			m_TwoPlayer->B = 255;
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_ThreePlayer))
	{
		m_ThreePlayer->B = 0;
		if (INPUT->GetButtonDown())
			m_NumOfPlayer = 3;
	}
	else
	{
		if (m_NumOfPlayer != 3)
			m_ThreePlayer->B = 255;
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_FourPlayer))
	{
		m_FourPlayer->B = 0;
		if (INPUT->GetButtonDown())
			m_NumOfPlayer = 4;
	}
	else
	{
		if (m_NumOfPlayer != 4)
			m_FourPlayer->B = 255;
	}
	if (m_NumOfPlayer > 0)
	{
		if (CollisionMgr::GetInst()->MouseWithBoxSize(m_EnterButton) && INPUT->GetButtonDown())
		{
			GameMgr::GetInst()->PlayerNumSetting(m_NumOfPlayer);
			SceneDirector::GetInst()->ChangeScene(new GameScene());
		}
	}
}

void NumofPlayerScene::Render()
{
	m_BG->Render();
	m_TwoPlayer->Render();
	m_ThreePlayer->Render();
	m_FourPlayer->Render();

	if(m_NumOfPlayer > 0)
		m_EnterButton->Render();
}
