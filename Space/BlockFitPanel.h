#pragma once
class BlockFitPanel : public Object
{
	Sprite* m_FitPanel;
	Sprite* m_CloseButton;
	Sprite* m_NextButton;
	Sprite* m_PrevButton;
	Sprite* m_DeicisonButton;

	TextMgr* m_BlockNumText;
public:
	BlockFitPanel(Block* block,int owner);
	~BlockFitPanel();

	int m_Number;
	int m_Owner;
	Block* m_FittingBlock;

	void Update(float deltaTime, float Time);
	void Render();
};

