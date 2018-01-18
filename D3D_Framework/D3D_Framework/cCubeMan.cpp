#include "stdafx.h"
#include "cCubeMan.h"
#include "cCubeParts.h"

cCubeMan::cCubeMan()
	: m_pRootNode(NULL)
	, m_pTexture(NULL)
{
}

cCubeMan::~cCubeMan()
{
}

void cCubeMan::Setup(const CHAR* pTextureFileName)
{
	if (pTextureFileName)
	{
		D3DXCreateTextureFromFile(D_DEVICE, pTextureFileName, &m_pTexture);
	}

	this->SetCubeParts();
}

void cCubeMan::Release()
{
	cCharacter::Release();
	D_SAFE_RELEASE(m_pTexture);
}

void cCubeMan::Update()
{
	cCharacter::Update();

	if (m_pRootNode)
		m_pRootNode->Update();
}

void cCubeMan::Render()
{
	cCharacter::Render();

	D_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	if (m_pTexture) D_DEVICE->SetTexture(0, m_pTexture);
	else D_DEVICE->SetTexture(0, NULL);

	if (m_pRootNode)
		m_pRootNode->Render();
}

void cCubeMan::SetCubeParts()
{
	float fDeltaX = 0.15F;

	cCubeParts* pBody = new cCubeParts();
	pBody->Setup(D3DXVECTOR3(0.4F, 0.6F, 0.2F), D3DXVECTOR3(0.F, 0.F, 0.F), D3DXVECTOR3(0.F, 0.F, 0.F));
	pBody->SetParentWorldTM(&m_matWorldTM);
	m_pRootNode = pBody;

	cCubeParts* pHead = new cCubeParts();
	pHead->Setup(D3DXVECTOR3(0.4F, 0.4F, 0.4F), D3DXVECTOR3(0.F, 0.F, 0.F), D3DXVECTOR3(0.F, 0.5F, 0.F));
	m_pRootNode->AddChild(pHead);

	cCubeParts* pLeftArm = new cCubeParts();
	pLeftArm->Setup(D3DXVECTOR3(0.2F, 0.6F, 0.2F), D3DXVECTOR3(-0.3F, -0.3F, 0.F), D3DXVECTOR3(0.F, 0.3F, 0.F));
	pLeftArm->SetAniDeltaX(fDeltaX);
	m_pRootNode->AddChild(pLeftArm);

	cCubeParts* pRightArm = new cCubeParts();
	pRightArm->Setup(D3DXVECTOR3(0.2F, 0.6F, 0.2F), D3DXVECTOR3(0.3F, -0.3F, 0.F), D3DXVECTOR3(0.F, 0.3F, 0.F));
	pRightArm->SetAniDeltaX(-fDeltaX);
	m_pRootNode->AddChild(pRightArm);

	cCubeParts* pLeftLeg = new cCubeParts();
	pLeftLeg->Setup(D3DXVECTOR3(0.2F, 0.6F, 0.2F), D3DXVECTOR3(-0.1F, -0.3F, 0.F), D3DXVECTOR3(0.F, -0.3F, 0.F));
	pLeftLeg->SetAniDeltaX(-fDeltaX);
	m_pRootNode->AddChild(pLeftLeg);

	cCubeParts* pRightLeg = new cCubeParts();
	pRightLeg->Setup(D3DXVECTOR3(0.2F, 0.6F, 0.2F), D3DXVECTOR3(0.1F, -0.3F, 0.F), D3DXVECTOR3(0.F, -0.3F, 0.F));
	pRightLeg->SetAniDeltaX(fDeltaX);
	m_pRootNode->AddChild(pRightLeg);
}