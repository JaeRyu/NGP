#pragma once
#include "Objects.h"
class CEnemy :
	public CObjects
{
private:
	int iType;
	int iHp;
	INFO m_tInfo;
	
public:
	//void Initialize(void);
	int Update(void);
	EnemyInfo GetPos(void);
	RECT GetRect(void)
	{
		RECT rc;
		if (iType < 10)
		{
			rc.left = m_tInfo.posX;
			rc.right = m_tInfo.posX + 50;
			rc.bottom = m_tInfo.posY + 50;
			rc.top = m_tInfo.posY;
		}
		else
		{
			rc.left = m_tInfo.posX;
			rc.right = m_tInfo.posX + 100;
			rc.bottom = m_tInfo.posY + 100;
			rc.top = m_tInfo.posY;
		}
		
		return rc;
	}
public:

	CEnemy(short posX, short posY, int Type);
	~CEnemy();
};

