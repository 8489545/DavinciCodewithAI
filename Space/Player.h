#pragma once
struct ConjectureResult
{
	int playernum;
	int handnum;
	int blocknum;
	int percentage;
	Color blockcolor;
}Conjecture;
class Player : public Object
{
public:
	Player();
	~Player();

	int m_PlayerNum;
	bool m_isAI;
	bool m_isFittingBlock;

	std::vector<Block*> m_Hand;

	std::list<ConjectureResult*> m_Results;

	Block* m_PrevBlock;

	void SetPlayer(int num, bool ai);

 
	void BlockDist();
	void BlockInHand();
	void MoveJoker();
	void BlockFit();

	void BlockFitSuccess();
	void BlockFitFailed();

	void BlockPrediction();
	bool BlockCompare();

	void ProbabilityCaculation();

	void Update(float deltaTime,float Time);
	void Render();

};

