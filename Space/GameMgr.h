#pragma once
class GameMgr : public Singleton<GameMgr>
{
public:
	GameMgr();
	~GameMgr();

	int m_NumOfPlayer;

	std::vector<Block*> m_AllBlock;

	void Init();
	void Release();

	void BlockInitSetting();

	void CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos);
};

