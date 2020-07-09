#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetPlayer(int num, bool ai)
{
	m_PlayerNum = num;
	m_isAI = ai;
}

void Player::Update(float deltaTime, float Time)
{
}

void Player::Render()
{
}
