#pragma once
#include "Player.h"
class CBullet :
	public CPlayer
{
private:
	int Update(void);
	void Initialize(void);
	void Release(void);

public:
	CBullet();
	~CBullet();
};

