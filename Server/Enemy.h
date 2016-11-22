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
			rc.left = m_tInfo.posX+10;
			rc.right = m_tInfo.posX + 40;
			rc.bottom = m_tInfo.posY + 40;
			rc.top = m_tInfo.posY+10;
		}
		else
		{
			rc.left = m_tInfo.posX+20;
			rc.right = m_tInfo.posX + 80;
			rc.bottom = m_tInfo.posY + 80;
			rc.top = m_tInfo.posY+20;
		}
		
		return rc;
	}
public:

	CEnemy(short posX, short posY, int Type);
	~CEnemy();
};

