#pragma once
#include"windows.h"

typedef struct {
	WORD posX;
	WORD posY;
	BYTE state;
}INFO;

class CObjects
{
public:
	INFO info;
	CObjects();
	~CObjects();
};

