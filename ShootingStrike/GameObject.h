#pragma once
#include"userInclude.h"

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
	void SetInfo(INFO info);
	
protected:
	INFO m_info;
};
