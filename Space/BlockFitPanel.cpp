#include "stdafx.h"
#include "BlockFitPanel.h"

BlockFitPanel::BlockFitPanel(Block* block,int owner)
{
	m_FitPanel = Sprite::Create(L"Painting/BlockFit/FitPanel.png");
	m_FitPanel->SetParent(this);
	SetPosition(1600,900);
	m_CloseButton = Sprite::Create(L"Painting/BlockFit/CloseButton.png");

	m_FittingBlock = block;
	m_Owner = owner;
}

BlockFitPanel::~BlockFitPanel()
{
}

void BlockFitPanel::Update(float deltaTime, float Time)
{
	m_FittingBlock->m_ActiveBlock = true;
	m_CloseButton->SetPosition((m_Position.x + m_Size.x / 2) - m_CloseButton->m_Size.x / 2, (m_Position.y - m_Size.y / 2) + m_CloseButton->m_Size.y / 2);

	for (auto& iter : GameMgr::GetInst()->m_Players)
	{
		if (iter->m_PlayerNum == m_Owner)
		{
			iter->m_isFittingBlock = true;
		}
	}
}

void BlockFitPanel::Render()
{
	m_FitPanel->Render();
	m_CloseButton->Render();
}
