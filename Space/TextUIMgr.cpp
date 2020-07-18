#include "stdafx.h"
#include "TextUIMgr.h"

TextUIMgr::TextUIMgr()
{
}

TextUIMgr::~TextUIMgr()
{
}

void TextUIMgr::Init()
{
	m_NextKey = 0;
}

void TextUIMgr::Release()
{
}

void TextUIMgr::AddText(int height, bool bold, bool itailc, const std::string str, Vec2 pos)
{
	TextMgr* text = new(std::nothrow)TextMgr();
	if (text && text->Init(height, bold, itailc, str))
	{
		m_Texts.insert(std::make_pair(m_NextKey, text));
		
		TextInfo* info = new TextInfo();
		info->Position = pos;

		m_TextInfos.push_back(info);
		m_NextKey += 1;
	}
}

void TextUIMgr::InitText(int key, int height, bool bold, bool itailc, const std::string str)
{
	if (key >= m_NextKey)
		return;
	(*m_Texts.find(key)).second->Init(height, bold, itailc, str);
}

void TextUIMgr::InitText(int key, Vec2 Pos)
{
	if (key >= m_NextKey)
		return;
	m_TextInfos[key]->Position = Pos;
}

void TextUIMgr::InitText(int key, std::string str)
{
	if (key >= m_NextKey)
		return;
	m_TextInfos[key]->Str = str;
}

void TextUIMgr::Update()
{
}

void TextUIMgr::Render()
{
	Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	for (auto& iter : m_Texts)
	{
		iter.second->print(m_TextInfos[iter.first]->Str, m_TextInfos[iter.first]->Position.x, m_TextInfos[iter.first]->Position.y);
	}
	Renderer::GetInst()->GetSprite()->End();
}
