#include "stdafx.h"
#include "MainScene.h"
#include"NumofPlayerScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	m_BG = Sprite::Create(L"Painting/Main/BG.png");
	m_BG->SetPosition(1920 / 2, 1080 / 2);
	
	m_Start = Sprite::Create(L"Painting/Main/Start.png");
	m_Start->SetPosition(1920 / 2, 700);

	m_HowTo = Sprite::Create(L"Painting/Main/HowTo.png");
	m_HowTo->SetPosition(1920 / 2, 850);

	m_Exit = Sprite::Create(L"Painting/Main/Exit.png");
	m_Exit->SetPosition(1920 / 2, 1000);

	m_Text = new TextMgr();
	m_Text->Init(32, true, false, "Arial");
	m_Text->SetColor(255, 255, 255, 255);
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float time)
{
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Start))
	{
		m_Start->SetScale(1.25f, 1.25f);

		if (INPUT->GetButtonDown())
		{
			SceneDirector::GetInst()->ChangeScene(new NumofPlayerScene());
			return;
		}
	}
	else
	{
		m_Start->SetScale(1.f, 1.f);
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_HowTo))
	{
		m_HowTo->SetScale(1.25f, 1.25f);
	}
	else
	{
		m_HowTo->SetScale(1.f, 1.f);
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Exit))
	{
		m_Exit->SetScale(1.25f, 1.25f);
	}
	else
	{
		m_Exit->SetScale(1.f, 1.f);
	}

}

void MainScene::Render()
{
	m_BG->Render();
	m_Start->Render();
	m_HowTo->Render();
	m_Exit->Render();

	Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	m_Text->print(std::to_string(INPUT->GetMousePos().x) + " " + std::to_string(INPUT->GetMousePos().y) + " \n" +
		std::to_string(dt) + " " +std::to_string(gt) , 0, 0);
	Renderer::GetInst()->GetSprite()->End();
}
