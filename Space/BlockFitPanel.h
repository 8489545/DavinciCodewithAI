#pragma once
class BlockFitPanel : public Object
{
	Sprite* m_CloseButton;
	Sprite* m_FitPanel;
public:
	BlockFitPanel(Block* block,int owner);
	~BlockFitPanel();

	int m_Owner;
	Block* m_FittingBlock;

	void Update(float deltaTime, float Time);
	void Render();
};

