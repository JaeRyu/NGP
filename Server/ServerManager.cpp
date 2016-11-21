#include <algorithm>

#include "ServerManager.h"



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
	


	for(itor = lBullet.begin(); itor != lBullet.end(); ++itor)
	{
		itor->Update();
	}
	

	if (keyData.key[4])
	{
		printf("call spacebar client: %d\n", clientNum);
		CBullet tBullet;
		tBullet.SetType(0);
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

std::vector<CPlayer> CServerManager::GetPlayers(void)
{
	return vPlayer;
}


std::list<CBullet> CServerManager::GetBulletsLIst(void)
{
	return lBullet;
}

int CServerManager::GetMapY(void)
{
	return 0;
}


bool CServerManager::CirCleToCircle(INFO iA, INFO iB, int r1, int r2)
{
	return false;
}

bool CServerManager::OutOfRange(CObjects& obj)
{
	if (obj.GetInfo().posX < -50 && obj.GetInfo().posX > 500 && obj.GetInfo().posY < -50 && obj.GetInfo().posX > 850)
		return true;
	else
		return false;
}


CServerManager::CServerManager()
{
}


CServerManager::~CServerManager()
{
}
