#include "stdafx.h"
#include "cParticle.h"

cParticle::cParticle()
	: m_pTexture(NULL)
{
}

cParticle::~cParticle()
{
}

void cParticle::Setup(const CHAR* pTextureFileName, int nVecSize, E_SETUP_KIND eKind)
{
	D3DXCreateTextureFromFile(D_DEVICE, pTextureFileName, &m_pTexture);
	//D3DXCreateTextureFromFileEx(D_DEVICE,
	//	pTextureFileName,
	//	D3DX_DEFAULT_NONPOW2,
	//	D3DX_DEFAULT_NONPOW2,
	//	D3DX_DEFAULT,
	//	0,
	//	D3DFMT_UNKNOWN,
	//	D3DPOOL_MANAGED,
	//	D3DX_FILTER_NONE,
	//	D3DX_DEFAULT,
	//	D3DCOLOR_XRGB(0, 0, 0),
	//	NULL,
	//	NULL,
	//	&m_pTexture);

	m_vecPaticle.resize(nVecSize);

	switch (eKind)
	{
	case cParticle::E_SETUP_CIRCLE:

		for (size_t i = 0; i < m_vecPaticle.size(); i++)
		{
			float fRadius = rand() % 100 / 10.0f;
			m_vecPaticle[i].p = D3DXVECTOR3(0, 0, fRadius);

			D3DXVECTOR3 vAngle = D3DXVECTOR3(D3DXToRadian(rand() % 3600 / 10.0f),
				D3DXToRadian(rand() % 3600 / 10.0f),
				D3DXToRadian(rand() % 3600 / 10.0f));

			D3DXMATRIX matRX, matRY, matRZ, matT, matWorld;
			D3DXMatrixRotationX(&matRX, vAngle.x);
			D3DXMatrixRotationY(&matRY, vAngle.y);
			D3DXMatrixRotationZ(&matRZ, vAngle.z);

			D3DXMatrixTranslation(&matT, 0.F, 20.F, 0.F);
			matWorld = matT * matRX * matRY * matRZ;

			D3DXVec3TransformCoord(&m_vecPaticle[i].p,
				&m_vecPaticle[i].p,
				&matWorld);

			m_vecPaticle[i].c = D3DCOLOR_ARGB(255, 255, 255, 255);
		}

		break;

	case cParticle::E_SETUP_COLUMN:



		break;

	case cParticle::E_SETUP_SQUARE:

		for (size_t i = 0; i < m_vecPaticle.size(); i++)
		{
			m_vecPaticle[i].p = D3DXVECTOR3(D_RNDMANAGER->getFromFloatTo(-20.F, 20.F),
				D_RNDMANAGER->getFromFloatTo(0.F, 40.F),
				D_RNDMANAGER->getFromFloatTo(-20.F, 20.F));
			m_vecPaticle[i].c = D3DCOLOR_ARGB(255, 255, 255, 255);
		}

		break;
	}


	D_DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	D_DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	D_DEVICE->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	D_DEVICE->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(2.5f));
	D_DEVICE->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(5.0f));

	D_DEVICE->SetRenderState(D3DRS_POINTSIZE, FtoDw(50.0f));
	D_DEVICE->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.2f));
	D_DEVICE->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(100.f));

	D_DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	D_DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	D_DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	D_DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	D_DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D_DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

void cParticle::Release()
{
	D_SAFE_RELEASE(m_pTexture);
}

void cParticle::Update()
{
	static int nAlpha = 0;
	static int nDelta = 1;
	nAlpha += nDelta;

	if (nAlpha > 255)
	{
		nAlpha = 255;
		nDelta *= -1;
	}

	if (nAlpha < 150)
	{
		nAlpha = 150;
		nDelta *= -1;
	}

	for (size_t i = 0; i < m_vecPaticle.size(); i++)
	{
		if (m_vecPaticle[i].p.y <= 0.F)
		{
			if (m_vecSnow.size() < 100000)
				m_vecSnow.push_back(m_vecPaticle[i]);

			m_vecPaticle[i].p = D3DXVECTOR3(D_RNDMANAGER->getFromFloatTo(-20.F, 20.F),
				40.F,
				D_RNDMANAGER->getFromFloatTo(-20.F, 20.F));
		}

		m_vecPaticle[i].p.y -= D_RNDMANAGER->getFromFloatTo(0.02F, 0.1F);
		m_vecPaticle[i].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);
	}
}

void cParticle::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D_DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

	D_DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	D_DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	D_DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);

	D_DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	D_DEVICE->SetTexture(0, m_pTexture);

	D_DEVICE->DrawPrimitiveUP(D3DPT_POINTLIST,
		m_vecPaticle.size(),
		&m_vecPaticle[0],
		sizeof(ST_PC_VERTEX));

	if (!m_vecSnow.empty())
	{
		D_DEVICE->DrawPrimitiveUP(D3DPT_POINTLIST,
			m_vecSnow.size(),
			&m_vecSnow[0],
			sizeof(ST_PC_VERTEX));
	}

	D_DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	D_DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D_DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);

	D_DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	D_DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, false);
}
