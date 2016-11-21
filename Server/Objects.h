#pragma once
#include "windows.h"
#include "Define.h"

class CObjects
{
protected:
	INFO m_tInfo;
public:
	void Move(int iX, int iY);
	RECT GetRect(void)
	{
		RECT rc;
		rc.left = m_tInfo.posX;
		rc.right = m_tInfo.posX + 50;
		rc.bottom = m_tInfo.posY + 50;
		rc.top = m_tInfo.posY;
		return rc;
	}
	void SetInfo(INFO tInfo)
	{
		m_tInfo = tInfo;
	}
	INFO GetInfo(void)
	{
		return m_tInfo;
	}
	void ChangeState(int state) 
	{
		m_tInfo.state = state;
	}
public:
	CObjects();
	~CObjects();
};

