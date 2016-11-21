#pragma once
#include <vector>
#include <list>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
class CServerManager
{
	std::vector<CPlayer> vPlayer;
	std::list<CBullet> lBullet;
	std::list<CEnemy> m_listEnemy;
	//std::vector<> // 적 이 들어갈 콘테이너


	//충돌체크 함수
	bool CirCleToCircle(INFO iA, INFO iB, int r1, int r2); // A의 좌표, B의 좌표, A의 범위, B의 범위
	bool OutOfRange(CObjects& obj);
	bool Rect_To_Rect(RECT Bullet, RECT Monster);

public:
	void update(KEYDATA keyData);
	void AddPlayer(void);
	std::vector<CPlayer> GetPlayers(void);
	std::list<CBullet> GetBulletsLIst(void);
	std::list<CEnemy> GetMonster(void);
	int GetMapY(void);
	CServerManager();
	~CServerManager();
};

