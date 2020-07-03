#include "stdafx.h"
#include "CollisionMgr.h"


CollisionMgr::CollisionMgr()
{
}


CollisionMgr::~CollisionMgr()
{
}

bool CollisionMgr::MouseWithBoxSize(Object* obj)
{
	POINT Mouse;

	Mouse.x = INPUT->GetMousePos().x;
	Mouse.y = INPUT->GetMousePos().y;

	if (PtInRect(&obj->m_Collision, Mouse))
		return true;

	return false;
}