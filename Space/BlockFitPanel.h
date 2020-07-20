#pragma once
class BlockFitPanel : public Object
{
	Sprite* m_CloseButton;
	Sprite* m_FitPanel;
public:
	BlockFitPanel(Block* block);
	~BlockFitPanel();

	void Update(float deltaTime, float Time);
	void Render();
};

