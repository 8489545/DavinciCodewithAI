#pragma once
constexpr int PHASEUI = 0;
constexpr int TURNUI = 1;
class GameScene : public Scene
{
	Sprite* m_BG;
	Sprite* m_Table;

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
	void ImportBlock();
	void MoveJokerPos();
	void BlockFit();

	void Update(float deltaTime, float Time);
	void Render();
};

