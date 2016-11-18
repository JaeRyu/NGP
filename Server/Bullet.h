#pragma once
#include "Player.h"
class CBullet :
	public CPlayer
{
private:
	/*À¯ÀúÃÑ¾Ë : 0, ÀûÃÑ¾Ë : 1 */
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

