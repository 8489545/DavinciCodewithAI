#pragma once
enum class Color
{
	WHITE,
	BLACK,
	NONE
};
class GameMgr : public Singleton<GameMgr>
{
public:
	GameMgr();
	~GameMgr();

	int m_NumOfPlayer;

	void Init();
	void Release();

	void CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos);
};

