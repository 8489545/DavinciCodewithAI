#pragma once
class MainScene : public Scene
{
	Sprite* m_BG;
	Sprite* m_Start;
	Sprite* m_HowTo;
	Sprite* m_Exit;

	TextMgr* m_Text;
public:
	MainScene();
	~MainScene();

	void Init();
	void Release();

	void Update(float deltaTime,float time);
	void Render();
};

