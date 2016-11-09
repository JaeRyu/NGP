#pragma once
#include "windows.h"
#include "Define.h"

class CObjects
{
protected:
	INFO m_tInfo;
	KEYDATA m_PlayerMove;
	
public:
	void Move(int iX, int iY);

	KEYDATA GetKeyData(void)
	{
		return m_PlayerMove;
	}
	void SetKeyData(KEYDATA tPlayerMove)
	{
		m_PlayerMove = tPlayerMove;
	}
	void SetInfo(INFO tInfo)
	{
		m_tInfo = tInfo;
	}
	INFO GetInfo(void)
	{
		return m_tInfo;
	}

public:
	CObjects();
	~CObjects();
};

