#pragma once
#include "Objects.h"
class CPlayer :
	public CObjects
{
	KEYDATA m_PlayerMove;
public:
	int Update(void);
	void PlayerMove(void);
	void Initialize(void);
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

