#pragma once
#include"userInclude.h"

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
	void SetInfo(INFO info);
	INFO GetInfo();
protected:
	INFO m_info;
};
