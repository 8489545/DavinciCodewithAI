#pragma once
class Player : public Object
{
public:
	Player();
	~Player();

	int m_PlayerNum;
	bool m_isAI;
	bool m_isFittingBlock;

	std::vector<Block*> m_Hand;

	void SetPlayer(int num, bool ai);

	void BlockInHand();
	void MoveJoker();
	void BlockFit();

	void Update(float deltaTime,float Time);
	void Render();
};

