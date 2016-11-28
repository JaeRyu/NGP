#pragma once
#include <vector>
#include <list>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

struct FilePattern{
	int time;
	int mobNum;
	int posX;
	int posY;
	int dx;
	int dy;
};

class CServerManager
{
	std::vector<CPlayer> vPlayer;
	std::list<CBullet> lBullet;
	std::list<CEnemy> m_listEnemy;
	std::vector<FilePattern> m_FilePattern;
	//std::vector<> // �� �� �� �����̳�
	DWORD dPlayTime;
	int clientScore[2];
	FILE *fPattern;
	int mobCount;
	//�浹üũ �Լ�
	bool CirCleToCircle(INFO iA, INFO iB, int r1, int r2); // A�� ��ǥ, B�� ��ǥ, A�� ����, B�� ����
	bool OutOfRange(CObjects& obj);
	bool Rect_To_Rect(RECT Bullet, RECT Monster);

public:
	void update(KEYDATA keyData);
	void AddPlayer(void);
	void SetPlayTime();
	void EnemyZeroTo(int n);
	int GetClientScore(int num);
	std::vector<CPlayer> GetPlayers(void);
	std::list<CBullet> GetBulletsLIst(void);
	std::list<CEnemy> GetMonster(void);
	int GetMapY(void);
	CServerManager();
	~CServerManager();
};

