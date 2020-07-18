#pragma once
class GameScene : public Scene
{
	Sprite* m_BG;
	Sprite* m_Table;

	Sprite* m_UIBlockDist;
	Sprite* m_UISetJokerPos;

	Sprite* m_JokerPosCompleteButton;
public:
	GameScene();
	~GameScene();

	int m_DistBlockNum;

	void Init();
	void Release(); 

	void BlockDist();
	void SetJokerPos();
	void SetOrder();
	void BlockFit();

	void Update(float deltaTime, float Time);
	void Render();
};

