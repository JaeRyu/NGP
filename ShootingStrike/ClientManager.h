#pragma once

#include"userInclude.h"


class CClientManager
{

	// 오브젝트 비트맵
	HBITMAP hPlayerBullet;
	HBITMAP hEnemyBullet;
	HBITMAP hPlane;
	HBITMAP hEnemy[11];
	HBITMAP hExplosion;
	HBITMAP hBackground;
	HBITMAP oldbit;
	HBRUSH redBrush;
	HBRUSH oldBrush;
	// 폰트
	HFONT hFontScore;
	HFONT oldFont;
	
	CSoundMgr SoundManager;
	int score; // 내점수
	int pscore; // 파트너 점수
	int gameState; // 게임상태
	int iHp; // 체력
public:
	bool DrawObejct(HDC hdc);
	bool DrawBackground(HDC hdc, int& mapY);
	void Init(HINSTANCE hInst);
	void DrawScore(HDC hdc);
	void SetScore(int s) { score = s; }
	void SetPScore(int s) { pscore = s; }
	void DrawDummy(HDC hdc);
	void DrawHP(HDC hdc);
	void DrawWaitScene(HDC hdc);
	void DrawEndScene(HDC hdc);
	void UpdateDummy();
	void ChangeGameState(int number);
	void SetHP(int h) { iHp = h; }
	int GetGameState();
public:
	std::vector<CPlane> vPlane;
	std::vector<CBullets> vBullet;
	std::vector<CEnemy> vEnemy;
	std::list<DESTROYED> vDestroy;
	int m_MapY;
public:
	CClientManager();
	~CClientManager();
};

