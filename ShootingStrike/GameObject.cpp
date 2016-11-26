#include"stdafx.h"
#include"GameObject.h"

CGameObject::CGameObject()
{
}
CGameObject::~CGameObject()
{

}

void CGameObject::SetInfo(INFO info)
{
	m_info = info;
}

INFO CGameObject::GetInfo()
{
	return m_info;
}
