#pragma once
#include "Player.h"
class CBullet :
	public CPlayer
{
private:
	/*À¯ÀúÃÑ¾Ë : 0, ÀûÃÑ¾Ë : 1 */
	int type;
	int client;
	int m_dx, m_dy; // ÃÑ¾Ë ¹æÇâ
private:
	void Initialize(void);
	void Release(void);
	
public:
	int GetType(void);
	void SetType(int tType);

	int GetClient();
	void SetClient(int c);

	void SetVector(int dx, int dy);
	
	int Update(void);

	IBULLET GetBulletInfo(void);
	CBullet();
	~CBullet();
};

