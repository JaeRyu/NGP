#pragma once
#include "Objects.h"
class CPlayer :
	public CObjects
{
private:
	KEYDATA m_PlayerMove;
	DWORD shootTime;
public:
	int Update(void);
	void PlayerMove(void);
	void Initialize(void);
	DWORD GetShootTime(void);
	void ResetTime(void);
public:
	CPlayer();
	~CPlayer();
public:
	KEYDATA GetKeyData(void)
	{
		return m_PlayerMove;
	}
	void SetKeyData(KEYDATA tPlayerMove)
	{
		m_PlayerMove = tPlayerMove;
	}
};

