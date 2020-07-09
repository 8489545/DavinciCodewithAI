#pragma once
class Player : public Object
{
public:
	Player();
	~Player();

	int m_PlayerNum;
	bool m_isAI;

	std::vector<Block*> m_Hand;

	void SetPlayer(int num, bool ai);

	void BlockInHand();

	void Update(float deltaTime,float Time);
	void Render();
};

