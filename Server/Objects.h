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
		rc.left = m_tInfo.posX+10;
		rc.right = m_tInfo.posX + 40;
		rc.bottom = m_tInfo.posY + 40;
		rc.top = m_tInfo.posY+10;
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

