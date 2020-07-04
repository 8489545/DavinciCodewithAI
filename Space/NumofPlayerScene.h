#pragma once
class NumofPlayerScene : public Scene
{
	Sprite* m_BG;
	Sprite* m_TwoPlayer;
	Sprite* m_ThreePlayer;
	Sprite* m_FourPlayer;

	Sprite* m_EnterButton;
public:
	NumofPlayerScene();
	~NumofPlayerScene();

	int m_NumOfPlayer;

	void Init();
	void Release();

	void Update(float deltaTime, float Time);
	void Render();
};

