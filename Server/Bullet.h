#pragma once
#include "Player.h"
class CBullet :
	public CPlayer
{
private:
	/*�����Ѿ� : 0, ���Ѿ� : 1 */
	int type;

private:
	void Initialize(void);
	void Release(void);
	
public:
	void SetType(int tType);
	int Update(void);
	IBULLET GetBulletInfo(void);
	CBullet();
	~CBullet();
};

