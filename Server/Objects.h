#pragma once
#include "windows.h"
#include "Define.h"

class CObjects
{
protected:
	INFO m_tInfo;
public:
	void Move(int iX, int iY);
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

