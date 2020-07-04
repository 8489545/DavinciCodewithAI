#pragma once
class GameScene : public Scene
{
	Sprite* m_BG;
	Sprite* m_Table;
public:
	GameScene();
	~GameScene();

	void Init();
	void Release();

	void Update(float deltaTime, float Time);
	void Render();
};

