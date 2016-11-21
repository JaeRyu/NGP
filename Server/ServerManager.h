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
	//std::vector<> // �� �� �� �����̳�


	//�浹üũ �Լ�
	bool CirCleToCircle(INFO iA, INFO iB, int r1, int r2); // A�� ��ǥ, B�� ��ǥ, A�� ����, B�� ����
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

