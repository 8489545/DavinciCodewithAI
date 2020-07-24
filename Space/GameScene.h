#pragma once

class GameScene : public Scene
{
	Sprite* m_BG;
	Sprite* m_Table;

	Sprite* m_JokerPosCompleteButton;
	Sprite* m_KeepFitButton;
	Sprite* m_StopFitButton;
public:
	GameScene();
	~GameScene();

	int m_DistBlockNum;

	void Init();
	void Release();

	void BlockDist();
	void SetOrder();
	void ImportBlock();
	void MoveJokerPos();
	void BlockFit();
	void NextAction();

	void Update(float deltaTime, float Time);
	void Render();
};

