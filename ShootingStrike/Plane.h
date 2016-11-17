#pragma once

#include"userInclude.h"

class CGameObject;

class CPlane : public CGameObject
{
public:
	CPlane();
	~CPlane();
	void Draw(HDC memdc, HBITMAP hPlane, HBITMAP oldbit);
};

