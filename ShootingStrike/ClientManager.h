#pragma once

#include"userInclude.h"


class CClientManager
{

	// ������Ʈ ��Ʈ��
	HBITMAP hPlayerBullet;
	HBITMAP hEnemyBullet;
	HBITMAP hPlane;
	HBITMAP hEnemy[11];
	HBITMAP hExplosion;
	HBITMAP hBackground;
	HBITMAP oldbit;

	// ��Ʈ
	HFONT hFontScore;
	HFONT oldFont;


	int score; // ������
	int gameState; // ���ӻ���

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

