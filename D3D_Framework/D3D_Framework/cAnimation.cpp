#include "stdafx.h"
#include "cAnimation.h"

cAnimation::cAnimation()
{
	D3DXMatrixIdentity(&m_matAnimation);
	D3DXMatrixIdentity(&m_matAniR);
	D3DXMatrixIdentity(&m_matAniT);
	D3DXMatrixIdentity(&m_matLocalTM);
}

cAnimation::~cAnimation()
{
}

void cAnimation::Setup()
{
}

void cAnimation::Release()
{
}

void cAnimation::Update(float* pFrame, D3DXMATRIXA16* pLocalTM)
{
	m_matLocalTM = (*pLocalTM);
	this->AnimationPosTrack(pFrame);
	this->AnimationRotTrack(pFrame);
	m_matAnimation = m_matAniR * m_matAniT;
}

void cAnimation::AnimationRotTrack(float* pFrame)
{
	D3DXMatrixIdentity(&m_matAniR);

	if (m_vecRotTrack.empty())
	{
		m_matAniR = m_matLocalTM;
		m_matAniR._41 = 0.F;
		m_matAniR._42 = 0.F;
		m_matAniR._43 = 0.F;
		return;
	}

	if ((*pFrame) <= m_vecRotTrack.front().ulFrame)
	{
		D3DXMatrixRotationQuaternion(&m_matAniR, 
			&m_vecRotTrack.front().sQuarter);
		return;
	}
	if ((*pFrame) >= m_vecRotTrack.back().ulFrame)
	{
		D3DXMatrixRotationQuaternion(&m_matAniR,
			&m_vecRotTrack.back().sQuarter);
		return;
	}
	
	int nNextIdx = 0;
	for (size_t i = 0; i < m_vecRotTrack.size(); i++)
	{
		if ((*pFrame) < m_vecRotTrack[i].ulFrame)
		{
			nNextIdx = i;
			break;
		}
	}

	float t = 0.F;
	NS_UTILS::GetInterpolationT(&t, m_vecRotTrack[nNextIdx - 1].ulFrame, 
		(*pFrame), m_vecRotTrack[nNextIdx].ulFrame);

	D3DXQUATERNION sQuarter;
	D3DXQuaternionSlerp(&sQuarter, &m_vecRotTrack[nNextIdx - 1].sQuarter,
		&m_vecRotTrack[nNextIdx].sQuarter, t);

	D3DXMatrixRotationQuaternion(&m_matAniR, &sQuarter);
}

void cAnimation::AnimationPosTrack(float* pFrame)
{
	D3DXMatrixIdentity(&m_matAniT);

	if (m_vecPosTrack.empty())
	{
		m_matAniT._41 = m_matLocalTM._41;
		m_matAniT._42 = m_matLocalTM._42;
		m_matAniT._43 = m_matLocalTM._43;
		return;
	}

	if ((*pFrame) <= m_vecPosTrack.front().ulFrame)
	{
		D3DXMatrixTranslation(&m_matAniT, m_vecPosTrack.front().vPosition.x,
			m_vecPosTrack.front().vPosition.y, m_vecPosTrack.front().vPosition.z);
		return;
	}
	if ((*pFrame) >= m_vecPosTrack.back().ulFrame)
	{
		D3DXMatrixTranslation(&m_matAniT, m_vecPosTrack.back().vPosition.x,
			m_vecPosTrack.back().vPosition.y, m_vecPosTrack.back().vPosition.z);
		return;
	}

	int nNextIdx = 0;
	for (size_t i = 0; i < m_vecPosTrack.size(); i++)
	{
		if ((*pFrame) < m_vecPosTrack[i].ulFrame)
		{
			nNextIdx = i;
			break;
		}
	}

	float t = 0.F;
	NS_UTILS::GetInterpolationT(&t, m_vecPosTrack[nNextIdx - 1].ulFrame,
		(*pFrame), m_vecPosTrack[nNextIdx].ulFrame);

	D3DXVECTOR3 vPosition;
	D3DXVec3Lerp(&vPosition, &m_vecPosTrack[nNextIdx - 1].vPosition,
		&m_vecPosTrack[nNextIdx].vPosition, t);

	D3DXMatrixTranslation(&m_matAniT, vPosition.x, vPosition.y, vPosition.z);
}
