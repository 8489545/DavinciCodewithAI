#pragma once
class GameScene : public Scene
{
	Sprite* m_BG;
	Sprite* m_Table;

	Sprite* m_UIBlockDist;
public:
	GameScene();
	~GameScene();

	void Init();
	void Release(); 

	void BlockDist();

	void Update(float deltaTime, float Time);
	void Render();
};

