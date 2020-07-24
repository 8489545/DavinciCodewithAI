#pragma once
#include<random>
#include<iterator>
#include<algorithm>
#include<functional>

enum class PHASE
{
	BlockDist,		//��� �й�
	SetOrder,		//���� ���ϱ�
	ImportBlock,	//��� ��������
	MoveJokerPos,	//������ ��Ŀ�� ��ġ ���ϱ�
	BlockFit,		//��� ���߱�
	SelectNextAct,	//������ �ൿ ����
	NONE
};
constexpr int ALLBLOCK = 1;
constexpr int BLOCKPILE = 2;

constexpr int PHASEUI = 0;
constexpr int TURNUI = 1;
constexpr int EVENTUI = 2;
class GameMgr : public Singleton<GameMgr>
{
public:
	GameMgr();
	~GameMgr();

	int m_NumOfPlayer;
	int m_Turn;
	int m_Cycle;
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
	Block* GetRandomBlock();
	Block* GetRandomBlockExcludingJoker();
	Block* GetActiveBlock(int num);

	void PlayerNumSetting(int num);
	void BlockInitSetting();
	void CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos);
	void BlockInHand(int playernum, Block* block);

	void BlockHandSetting();
	void BlockPileSetting();

	void MoveJoker(int owner);
	void MoveJoker(int owner, Block* block);

	void BlockFit(int owner);

	void NextTurn();
};