#pragma once
#include<vector>
#include<list>
#include"Player.h"
#include"Bullet.h"

class CServerManager
{
	std::vector<CPlayer> vPlayer;
	std::list<CBullet> lBullet;
	//std::vector<> // 적 이 들어갈 콘테이너


	//충돌체크 함수
	bool CirCleToCircle(INFO iA, INFO iB, int r1, int r2); // A의 좌표, B의 좌표, A의 범위, B의 범위
	bool OutOfRange(CObjects& obj);

public:
	void update(KEYDATA keyData);
	void AddPlayer(void);
	std::vector<CPlayer> GetPlayers(void);
	std::list<CBullet> GetBulletsLIst(void);
	int GetMapY(void);
	CServerManager();
	~CServerManager();
};

