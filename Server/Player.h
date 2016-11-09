#pragma once
#include "Objects.h"
class CPlayer :
	public CObjects
{

public:
	int Update(void);
	void PlayerMove(void);
	void Initialize(void);
public:
	CPlayer();
	~CPlayer();
};

