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

	// 폰트
	HFONT hFontScore;
	HFONT oldFont;


	int score; // 내점수
	int gameState; // 게임상태

public:
	bool DrawObejct(HDC hdc);
	bool DrawBackground(HDC hdc, int& mapY);
	void Init(HINSTANCE hInst);
	void DrawScore(HDC hdc);
	void SetScore(int s) { score = s; }
	void DrawDummy(HDC hdc);
	void UpdateDummy();
	void ChangeGameState(int number);
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

