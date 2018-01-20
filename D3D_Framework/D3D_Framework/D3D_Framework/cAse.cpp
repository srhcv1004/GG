#include "stdafx.h"
#include "cAse.h"
#include "cTexMtl.h"

cAse::cAse()
	: m_pTexMtl(NULL)
{
}

cAse::~cAse()
{
}

void cAse::Setup()
{
}

void cAse::Release()
{
	D_SAFE_RELEASE(m_pTexMtl);
	D_SAFE_DELETE(m_pTexMtl);
}

void cAse::Render()
{	
	if (m_pTexMtl)
	{
		D_DEVICE->SetTexture(0, m_pTexMtl->GetTex());
		D_DEVICE->SetFVF(ST_PNT_VERTEX::FVF);
		D_DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, (UINT)m_vecVertex.size() / (UINT)3,
			&m_vecVertex[0], sizeof(ST_PNT_VERTEX));
	}
}
