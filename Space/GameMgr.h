#pragma once
#include<random>
#include<iterator>
#include<algorithm>
#include<functional>

enum class PHASE
{
	BlockDist,		//블록 분배
	SetOrder,		//순서 정하기
	ImportBlock,	//블록 가져오기
	BlockFit,		//블록 맞추기
	KeepFit,		//계속 맞추기
	StopFit,		//그만 맞추기
	TurnClock,		//순서 넘기기
	NONE
};
class GameMgr : public Singleton<GameMgr>
{
public:
	GameMgr();
	~GameMgr();

	int m_NumOfPlayer;
	int m_Turn;
	PHASE m_GamePhase;

	PHASE GetGamePhase() { return m_GamePhase; }
	void SetGamePhase(PHASE phase) { m_GamePhase = phase; }

	std::vector<Block*> m_AllBlock;
	std::vector<Block*> m_BlockPile;
	std::vector<Player*> m_Players;

	Block* m_ActiveBlock;

	void Init();
	void Release();

	void Update();

	Player* GetPlayer(int num);

	void PlayerNumSetting(int num);
	void BlockInitSetting();
	void CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos);
	void BlockInHand(int playernum, Block* block);

	void BlockHandSetting();
	void BlockPileSetting();

	void NextTurn();
};