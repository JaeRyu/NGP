#include "Objects.h"


CObjects::CObjects()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_PlayerMove, sizeof(KEYDATA));
}


CObjects::~CObjects()
{
}
void CObjects::Move(int iX, int iY)
{
	m_tInfo.posX -= iX;
	m_tInfo.posY -= iY;
}