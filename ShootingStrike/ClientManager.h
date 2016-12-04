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
	HBRUSH redBrush;
	HBRUSH oldBrush;
	// ��Ʈ
	HFONT hFontScore;
	HFONT oldFont;
	
	CSoundMgr SoundManager;
	int score; // ������
	int pscore; // ��Ʈ�� ����
	int gameState; // ���ӻ���
	int iHp; // ü��
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

