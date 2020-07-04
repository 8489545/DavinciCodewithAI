#pragma once
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void Init();
	void Release();

	void Update(float deltaTime, float Time);
	void Render();
};

