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
	BlockFit,		//��� ���߱�
	KeepFit,		//��� ���߱�
	StopFit,		//�׸� ���߱�
	TurnClock,		//���� �ѱ��
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