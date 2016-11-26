#pragma once
#include "Objects.h"
class CEnemy :
	public CObjects
{
private:
	int iType;
	int iHp;

	int m_dx, m_dy;
	DWORD dTime;

	int shootRate; // ÃÑ¾Ë ¹ß»ç µô·¹ÀÌ

public:
	int Update(void);
	int SetVector(int dx, int dy);
	EnemyInfo GetPos(void);
	RECT GetRect(void);
	DWORD GetTime();
	void SetTimeZero();
	void SetShootRate(int p);
	int GetShootRate();
	void HitDamage(int damage);

public:

	CEnemy(short posX, short posY, int Type);
	~CEnemy();
};

