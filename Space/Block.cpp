#include "stdafx.h"
#include "Block.h"

Block::Block(int num, bool front, float rotation, int owner, Color color,Vec2 pos)
{
	m_BlockNumber = num;
	m_Front = front;
	m_Owner = owner;
	m_Color = color;

	std::wstring colorstr;
	if (m_Color == Color::BLACK)
		colorstr = L"Black";
	else if (m_Color == Color::WHITE)
		colorstr = L"White";

	m_Back = Sprite::Create(L"Painting/Block/Back_" + colorstr + L".png");
	m_Active = Sprite::Create(L"Painting/Block/Active.png");

	m_Block = Sprite::Create(L"Painting/Block/" + colorstr +std::to_wstring(num) + L".png");
	m_Block->SetParent(this);
	m_Position = pos;
	m_Rotation = rotation;
	m_ActiveBlock = false;
}

Block::~Block()
{
}

void Block::Update(float deltaTime, float Time)
{
	m_Back->m_Position = m_Position;
	m_Active->m_Position = m_Position;
	m_Back->m_Rotation = m_Rotation;

	if (CollisionMgr::GetInst()->MouseWithBoxSize(this))
	{
		m_ActiveBlock = true;
	}
	else
	{
		m_ActiveBlock = false;
	}
}

void Block::Render()
{
	m_Block->Render();
	if(!m_Front)
		m_Back->Render();
	if (m_ActiveBlock)
		m_Active->Render();
}
