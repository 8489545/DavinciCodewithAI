#pragma once
class NumofPlayerScene : public Scene
{
public:
	NumofPlayerScene();
	~NumofPlayerScene();

	void Init();
	void Release();

	void Update(float deltaTime, float Time);
	void Render();
};

