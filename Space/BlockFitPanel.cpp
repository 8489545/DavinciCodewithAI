#include "stdafx.h"
#include "BlockFitPanel.h"

BlockFitPanel::BlockFitPanel(Block* block,int owner)
{
	m_FitPanel = Sprite::Create(L"Painting/BlockFit/FitPanel.png");
	m_FitPanel->SetParent(this);
	SetPosition(1600,900);
	m_CloseButton = Sprite::Create(L"Painting/BlockFit/CloseButton.png");
	m_NextButton = Sprite::Create(L"Painting/BlockFit/NextButton.png");
	m_PrevButton = Sprite::Create(L"Painting/BlockFit/PrevButton.png");
	m_DeicisonButton = Sprite::Create(L"Painting/BlockFit/DecisionButton.png");

	m_CloseButton->SetPosition((m_Position.x + m_Size.x / 2) - m_CloseButton->m_Size.x / 2, (m_Position.y - m_Size.y / 2) + m_CloseButton->m_Size.y / 2);

	m_NextButton->SetPosition(m_Position.x + 100, m_Position.y);
	m_PrevButton->SetPosition(m_Position.x - 100, m_Position.y);

	m_DeicisonButton->SetPosition((m_Position.x - m_Size.x / 2) + m_CloseButton->m_Size.x / 2, (m_Position.y + m_Size.y / 2) - m_CloseButton->m_Size.y / 2);

	m_FittingBlock = block;
	m_Owner = owner;

	m_BlockNumText = new TextMgr();
	m_BlockNumText->Init(72, true, false, "Arial");

	m_Number = 0;
}

BlockFitPanel::~BlockFitPanel()
{
}

void BlockFitPanel::Update(float deltaTime, float Time)
{
	m_FittingBlock->m_ActiveBlock = true;
	m_CloseButton->SetPosition((m_Position.x + m_Size.x / 2) - m_CloseButton->m_Size.x / 2, (m_Position.y - m_Size.y / 2) + m_CloseButton->m_Size.y / 2);
	m_DeicisonButton->SetPosition((m_Position.x - m_Size.x / 2) + m_DeicisonButton->m_Size.x / 2, (m_Position.y + m_Size.y / 2) - m_DeicisonButton->m_Size.y / 2);
	m_NextButton->SetPosition(m_Position.x + 100, m_Position.y);
	m_PrevButton->SetPosition(m_Position.x - 100, m_Position.y);

	for (auto& iter : GameMgr::GetInst()->m_Players)
	{
		if (iter->m_PlayerNum == m_Owner)
		{
			iter->m_isFittingBlock = true;
		}
	}

	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_PrevButton) && INPUT->GetButtonDown())
	{
		INPUT->ButtonDown(false);
		if (m_Number > 0)
		{
			m_Number -= 1;
		}
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_NextButton) && INPUT->GetButtonDown())
	{
		INPUT->ButtonDown(false);
		if (m_Number < 12)
		{
			m_Number += 1;
		}
	}
	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_DeicisonButton) && INPUT->GetButtonDown())
	{
		INPUT->ButtonDown(false);
		if (m_Number == m_FittingBlock->m_BlockNumber)
		{
			m_FittingBlock->m_Front = true;
			m_FittingBlock->m_isRevealedBlock = true;
			TextUIMgr::GetInst()->InitText(EVENTUI, "Player" + std::to_string(m_Owner) + "이 Player" + std::to_string(m_FittingBlock->m_Owner) + "의 블록을 맞췄습니다.");
			for (auto& iter : GameMgr::GetInst()->m_Players)
			{
				if (iter->m_PlayerNum == m_Owner)
				{
					m_BlockNumText->Release();
					m_FittingBlock->m_ActiveBlock = false;
					iter->m_isFittingBlock = false;
					INPUT->ButtonDown(false);
					SetDestroy(true);
				}
			}
			GameMgr::GetInst()->GetPlayer(m_Owner - 1)->BlockFitSuccess();
		}
		else
		{
			TextUIMgr::GetInst()->InitText(EVENTUI, "Player" + std::to_string(m_Owner) + "이 Player" + std::to_string(m_FittingBlock->m_Owner) + "의 블록을 맞추는데 실패했습니다.");
			for (auto& iter : GameMgr::GetInst()->m_Players)
			{
				if (iter->m_PlayerNum == m_Owner)
				{
					m_BlockNumText->Release();
					m_FittingBlock->m_ActiveBlock = false;
					iter->m_isFittingBlock = false;
					INPUT->ButtonDown(false);
					SetDestroy(true);
				}
			}
			GameMgr::GetInst()->GetPlayer(m_Owner - 1)->BlockFitFailed();
		}
	}

	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_CloseButton) && INPUT->GetButtonDown())
	{
		for (auto& iter : GameMgr::GetInst()->m_Players)
		{
			if (iter->m_PlayerNum == m_Owner)
			{
				m_BlockNumText->Release();
				m_FittingBlock->m_ActiveBlock = false;
				iter->m_isFittingBlock = false;
				INPUT->ButtonDown(false);
				SetDestroy(true);
			}
		}
	}
}

void BlockFitPanel::Render()
{
	m_FitPanel->Render();
	m_CloseButton->Render();
	m_NextButton->Render();
	m_PrevButton->Render();
	m_DeicisonButton->Render();

	Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	if(m_Number == 12)
		m_BlockNumText->print("-", m_Position.x - 25, m_Position.y - 30);
	else
		m_BlockNumText->print(std::to_string(m_Number), m_Position.x - 25, m_Position.y - 30);
	Renderer::GetInst()->GetSprite()->End();
}
