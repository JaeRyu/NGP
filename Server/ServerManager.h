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
	
	KEYDATA playerKey[2];

	DWORD dPlayTime;
	int clientScore[2];
	int iHpTemp;
	FILE *fPattern;
	int mobCount;
	int iGameState;
	//충돌체크 함수
	bool CirCleToCircle(INFO iA, INFO iB, int r1, int r2); // A의 좌표, B의 좌표, A의 범위, B의 범위
	bool OutOfRange(CObjects& obj);
	bool Rect_To_Rect(RECT Bullet, RECT Monster);

public:
	int GetState(void)
	{
		return iGameState;
	}
	void ChangeState(int iA)
	{
		iGameState = iA;
	}
	void Update();
	void UpdatePlayer(KEYDATA keyData);
	void AddPlayer(void);
	void SetPlayTime();
	void EnemyZeroTo(int n);
	void SetKeyData(KEYDATA k);
	int GetClientScore(int num);
	std::vector<CPlayer> GetPlayers(void);
	std::list<CBullet> GetBulletsLIst(void);
	std::list<CEnemy> GetMonster(void);
	int GetMapY(void);
	CServerManager();
	~CServerManager();
};

