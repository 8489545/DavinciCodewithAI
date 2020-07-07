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
	PHASE m_GamePhase;

	PHASE GetGamePhase() { return m_GamePhase; }
	void SetGamePhase(PHASE phase) { m_GamePhase = phase; }

	std::vector<Block*> m_AllBlock;

	std::vector<Block*> m_BlockPile;

	std::vector<Block*> m_Player1Hand;
	std::vector<Block*> m_Player2Hand;
	std::vector<Block*> m_Player3Hand;
	std::vector<Block*> m_Player4Hand;

	Block* m_ActiveBlock;

	void Init();
	void Release();

	void Update();

	void BlockInitSetting();
	void CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos);
	void BlockInHand(int playernum, Block* block);

	void BlockHandSetting();
};