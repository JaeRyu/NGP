#pragma once
#include "Player.h"
class CBullet :
	public CPlayer
{
private:
	/*À¯ÀúÃÑ¾Ë : 0, ÀûÃÑ¾Ë : 1 */
	int type;
	int client;
private:
	void Initialize(void);
	void Release(void);
	
public:
	void SetType(int tType);
	void SetClient(int c);
	int GetClient();
	int Update(void);
	int GetType(void)
	{
		return type;
	}


	IBULLET GetBulletInfo(void);
	CBullet();
	~CBullet();
};

