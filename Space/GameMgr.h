#pragma once
class GameMgr : public Singleton<GameMgr>
{
public:
	GameMgr();
	~GameMgr();

	void Init();
	void Release();
};

