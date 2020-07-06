#pragma once
#include<random>
#include<iterator>
#include<algorithm>
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

	void Init();
	void Release();

	void BlockInitSetting();

	void CreateBlock(int num, bool front, float rotation, int owner, Color color, Vec2 pos);
};

