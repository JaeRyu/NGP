#include <algorithm>
#include <iostream>
#include "ServerManager.h"
#include "Enemy.h"

#define PI 3.141592f

using namespace std;


void CServerManager::update(KEYDATA keyData)
{

	int clientNum = keyData.clientNum;

	if (clientNum != -1)
	{
		vPlayer[clientNum].SetKeyData(keyData);
		vPlayer[clientNum].Update();
	}
	
	if (m_FilePattern.size() > 0)
	{
		while (m_FilePattern[mobCount].time < GetTickCount() - dPlayTime) //몹추가
		{
			FilePattern fp = m_FilePattern[mobCount];
			CEnemy tEnemy(fp.posX, fp.posY, fp.mobNum);
			tEnemy.SetVector(fp.dx, fp.dy);
			int rate = (rand() % 5 * 100) + 700;
			//printf("rate : %d\n", rate);
			tEnemy.SetShootRate(rate);

			m_listEnemy.push_back(tEnemy);

			mobCount++;
			if (m_FilePattern.size() == mobCount)
			{
				dPlayTime = GetTickCount();
				mobCount = 0;
			}
		}
	}
	

	std::list<CBullet>::iterator itor;
	
	// 총알 삭제 연산
	lBullet.remove_if([](CBullet& a) {    
		return a.GetInfo().state == 0;
	});

	std::list<CEnemy>::iterator iter;
	// 적 삭제 연산
	m_listEnemy.remove_if([](CEnemy &E) { 
		return E.GetInfo().state == 2;
	});
	


	for(itor = lBullet.begin(); itor != lBullet.end(); ++itor) // 충돌체크 연산
	{
		itor->Update();
		int iType;
		iType = itor->GetType();
		
		if (iType == 0)
		{
			for (iter = m_listEnemy.begin(); iter != m_listEnemy.end(); ++iter)
			{
				if (Rect_To_Rect(iter->GetRect(), itor->GetRect()))
				{
					clientScore[itor->GetClient()]+=10;
					INFO Temp = itor->GetInfo();
					Temp.state = 0;
					itor->SetInfo(Temp);


					iter->HitDamage(10);

				}
			}
		}
	}
	
	for (iter = m_listEnemy.begin(); iter != m_listEnemy.end(); ++iter) // 총알 탄막 연산
	{
		iter->Update();

		if (iter->GetPos().type > 10 && iter->GetTime() > 4000) 
		{
			CBullet tBullet;
			tBullet.SetType(1);
			INFO tInfo;
			tInfo.posX = iter->GetInfo().posX + 50;
			tInfo.posY = iter->GetInfo().posY + 50;
			tInfo.state = 1;
			tBullet.SetInfo(tInfo);
			for (int i = 1 ; i < 360; i += 10)
			{
				tBullet.SetVector( 5 * cosf(i * PI / 180.f), 5 * sinf(i * PI / 180.f));
				lBullet.push_back(tBullet);
			}
			iter->SetTimeZero();
		}

		if (iter->GetInfo().state == 1 && iter->GetPos().type < 10 && iter->GetTime() > iter->GetShootRate()) // 일반몹의 경우 0.7초에 한번씩
		{
			CBullet tBullet;
			tBullet.SetType(1);
			INFO tInfo;
			tInfo.posX = iter->GetInfo().posX + 25;
			tInfo.posY = iter->GetInfo().posY + 25;
			tInfo.state = 1;
			tBullet.SetInfo(tInfo);
			tBullet.SetVector(0, 5);
			lBullet.push_back(tBullet);
			iter->SetTimeZero();

		}
	}

	if (keyData.key[4])
	{
		//printf("call spacebar client: %d\n", clientNum);
		CBullet tBullet;
		tBullet.SetType(0);
		tBullet.SetClient(keyData.clientNum);
		INFO tInfo;
		tInfo.posX = vPlayer[clientNum].GetInfo().posX;
		tInfo.posY = vPlayer[clientNum].GetInfo().posY;
		tInfo.state = 1;
		tBullet.SetInfo(tInfo);
		tBullet.SetVector(0, -8);
		lBullet.push_back(tBullet);
		//printf("[%d 번 클라]총알생성\n", clientNum);
	}

}

void CServerManager::AddPlayer()
{
	vPlayer.push_back(CPlayer());
}

void CServerManager::SetPlayTime()
{
	dPlayTime = GetTickCount();
}

void CServerManager::EnemyZeroTo(int n)
{
	std::list<CEnemy>::iterator iter;
	for (iter = m_listEnemy.begin(); iter != m_listEnemy.end(); ++iter)
	{
		if (iter->GetInfo().state == 0)
			iter->ChangeState(n);
	}
}

int CServerManager::GetClientScore(int num)
{
	return clientScore[num];
}

std::vector<CPlayer> CServerManager::GetPlayers(void)
{
	return vPlayer;
}


std::list<CBullet> CServerManager::GetBulletsLIst(void)
{
	return lBullet;
}

std::list<CEnemy> CServerManager::GetMonster(void)
{
	return m_listEnemy;
}

int CServerManager::GetMapY(void)
{
	return 0;
}


bool CServerManager::CirCleToCircle(INFO iA, INFO iB, int r1, int r2)
{
	RECT rc;
	//50 by 50

	//보스 100 by 100
	

	return false;
}

bool CServerManager::OutOfRange(CObjects& obj)
{
	if (obj.GetInfo().posX < -50 && obj.GetInfo().posX > 500 && obj.GetInfo().posY < -50 && obj.GetInfo().posX > 850)
		return true;
	else
		return false;
}

bool CServerManager::Rect_To_Rect(RECT Bullet, RECT Monster)
{
	//일단 Enemy클래스를 만들자.
	RECT rc;
	if (IntersectRect(&rc, &Bullet, &Monster))
	{
		//hp 깎아주고.
		//충돌판정이 되면.
		//cout << "충돌이 되었습니다. " << endl;
		return true;
	}
	else
		return false;
	
}


CServerManager::CServerManager()
{
	dPlayTime = GetTickCount();
	fPattern = fopen("Pattern.txt", "rb");
	mobCount = 0;
	FilePattern fp;
	char s[100];
	fgets(s,100,fPattern);
	while (fscanf(fPattern, "%d %d %d %d %d %d", &fp.time, &fp.mobNum, &fp.posX, &fp.posY, &fp.dx, &fp.dy) != EOF)
	{
		//printf("FileRead \n");
		m_FilePattern.push_back(fp);
	}
	//fscanf(fPattern, "%d %d %d %d %d %d");
	clientScore[0] = 0;
	clientScore[1] = 0;

	//CEnemy Temp(100, 150, 1);	//1번
	//Temp.SetVector(0, 0);
	CEnemy Temp2(300, 150, 11);	//11번
	Temp2.SetVector(0, 0);

	//m_listEnemy.push_back(Temp);
	//m_listEnemy.push_back(Temp2);
}


CServerManager::~CServerManager()
{
}
