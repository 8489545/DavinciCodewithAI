#pragma once
enum class Color
{
	WHITE,
	BLACK,
	NONE
};
class Block : public Object
{
	Sprite* m_Block;
	Sprite* m_Back;
	Sprite* m_Active;

public:
	Block(int num,bool front,float rotation,int owner,Color color,Vec2 pos);
	~Block();

	int m_BlockNumber;
	bool m_Front;
	bool m_ActiveBlock;
	int m_Owner;
	int m_HandNum;
	Color m_Color;

	void Update(float deltaTime, float Time);
	void Render();
};

