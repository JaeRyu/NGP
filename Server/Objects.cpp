#include "Objects.h"


CObjects::CObjects()
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tInfo.state = 1;
}


CObjects::~CObjects()
{
}
void CObjects::Move(int iX, int iY)
{
	m_tInfo.posX += iX;
	m_tInfo.posY += iY;
}