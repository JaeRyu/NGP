#include <algorithm>
#include <iostream>
#include "ServerManager.h"
#include "Enemy.h"

using namespace std;


void CServerManager::update(KEYDATA keyData)
{

	int clientNum = keyData.clientNum;

	if (clientNum != -1)
	{
		vPlayer[clientNum].SetKeyData(keyData);
		vPlayer[clientNum].Update();
	}
	


	std::list<CBullet>::iterator itor;
	
	lBullet.remove_if([](CBullet a) {
		return a.GetInfo().state == 0;
	});

	std::list<CEnemy>::iterator iter;

	m_listEnemy.remove_if([](CEnemy E) {
		return E.GetInfo().state == 0;
	});
	


	for(itor = lBullet.begin(); itor != lBullet.end(); ++itor)
	{
		int iType;
		itor->Update();
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
				}
			}
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
		lBullet.push_back(tBullet);
		//printf("[%d 번 클라]총알생성\n", clientNum);
	}

}

void CServerManager::AddPlayer()
{
	vPlayer.push_back(CPlayer());
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
	clientScore[0] = 0;
	clientScore[1] = 0;

	CEnemy Temp(100, 150, 1);	//1번
	CEnemy Temp2(300, 150, 11);	//11번

	m_listEnemy.push_back(Temp);
	m_listEnemy.push_back(Temp2);
}


CServerManager::~CServerManager()
{
}
