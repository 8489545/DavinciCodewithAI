#pragma once
class GameMgr : public Singleton<GameMgr>
{
public:
	GameMgr();
	~GameMgr();

	int m_NumOfPlayer;

	void Init();
	void Release();
};

