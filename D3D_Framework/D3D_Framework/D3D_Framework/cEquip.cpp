#include "stdafx.h"
#include "cEquip.h"
#include "cSkinnedMesh.h"
#include "cXPlayerAnimation.h"

cEquip::cEquip()
	: m_pXPlayerWorldTM(NULL)
	, m_pXPlayerAnimation(NULL)
	, m_eChangePartKind(E_PARTS_BODY)
	, m_arChangePartsNum()
{
}

cEquip::~cEquip()
{
}

void cEquip::Setup(D3DXMATRIXA16* pXPlayerWorldTM)
{
	m_pXPlayerWorldTM = pXPlayerWorldTM;
	this->SetupParts();
}

void cEquip::Release()
{
	for (size_t i = 0; i < m_vecSkinnedPlayer.size(); i++)
	{
		D_SAFE_RELEASE(m_vecSkinnedPlayer[i]);
		D_SAFE_DELETE(m_vecSkinnedPlayer[i]);
	}
}

void cEquip::Update()
{
	this->ChangeParts();

	for (size_t i = 0; i < m_vecSkinnedPlayer.size(); i++)
	{
		if (m_vecSkinnedPlayer[i])
			m_vecSkinnedPlayer[i]->Update();
	}
}

void cEquip::Render()
{
	D_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	this->RenderChangeKind();

	for (size_t i = 0; i < m_vecSkinnedPlayer.size(); i++)
	{
		if (m_vecSkinnedPlayer[i])
			m_vecSkinnedPlayer[i]->Render();
	}
}

void cEquip::SetupParts()
{
	m_vecSkinnedPlayer.resize(E_PARTS_END);

	// Head parts
	//cSkinnedMesh* pHand = new cSkinnedMesh();
	//pHand->Setup("XFile/XPlayer", "1.x");
	//pHand->SetMatWorldPtr(&m_matWorldTM);
	//m_vecSkinnedPlayer[E_PARTS_HEAD] = pHand;

	// Body parts
	cXItem* pXBody = 
 		(cXItem*)(D_ITEMMANAGER->FindItem(m_arChangePartsNum[E_PARTS_BODY], cItemManager::E_PARTS_BODY));
	m_vecSkinnedPlayer[E_PARTS_BODY] = pXBody->GetXItem();
	m_vecSkinnedPlayer[E_PARTS_BODY]->SetMatWorldPtr(m_pXPlayerWorldTM);

	// Hand parts
	cXItem* pXHand =
		(cXItem*)(D_ITEMMANAGER->FindItem(m_arChangePartsNum[E_PARTS_HAND], cItemManager::E_PARTS_HAND));
	m_vecSkinnedPlayer[E_PARTS_HAND] = pXHand->GetXItem();
	m_vecSkinnedPlayer[E_PARTS_HAND]->SetMatWorldPtr(m_pXPlayerWorldTM);

	// Leg parts
	cXItem* pXLeg =
		(cXItem*)(D_ITEMMANAGER->FindItem(m_arChangePartsNum[E_PARTS_LEG], cItemManager::E_PARTS_LEG));
	m_vecSkinnedPlayer[E_PARTS_LEG] = pXLeg->GetXItem();
	m_vecSkinnedPlayer[E_PARTS_LEG]->SetMatWorldPtr(m_pXPlayerWorldTM);
}

void cEquip::RenderChangeKind()
{
	CHAR str[512] = "";

	switch (m_eChangePartKind)
	{
		case cEquip::E_PARTS_BODY:
		{
			strncpy_s(str, 512, "[Body 체인지]", 512);
		}
		break;

		case cEquip::E_PARTS_HAND:
		{
			strncpy_s(str, 512, "[Hand 체인지]", 512);
		}
		break;

		case cEquip::E_PARTS_LEG:
		{
			strncpy_s(str, 512, "[Leg 체인지]", 512);
		}
		break;
	}

	D_FONTMANAGER->DrawFontText("TimerFont", str,
		NULL,
		RectMake(D_WINSIZEX / 2, D_WINSIZEY / 2, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
}

void cEquip::ChangeParts()
{
	if (D_KEYMANAGER->IsOnceKeyDown(VK_F1))
	{
		m_eChangePartKind = E_PARTS_BODY;
	}

	if (D_KEYMANAGER->IsOnceKeyDown(VK_F2))
	{
		m_eChangePartKind = E_PARTS_HAND;
	}

	if (D_KEYMANAGER->IsOnceKeyDown(VK_F3))
	{
		m_eChangePartKind = E_PARTS_LEG;
	}
	

	if (D_KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		if (m_arChangePartsNum[m_eChangePartKind] == 0) m_arChangePartsNum[m_eChangePartKind] = 1;
		else if (m_arChangePartsNum[m_eChangePartKind] == 1) m_arChangePartsNum[m_eChangePartKind] = 0;

		cXItem* pXParts =
			(cXItem*)(D_ITEMMANAGER->FindItem(m_arChangePartsNum[m_eChangePartKind], cItemManager::E_PARTS(m_eChangePartKind)));
		m_vecSkinnedPlayer[m_eChangePartKind] = pXParts->GetXItem();
		m_vecSkinnedPlayer[m_eChangePartKind]->SetMatWorldPtr(m_pXPlayerWorldTM);

		m_pXPlayerAnimation->AnimationChangeByState();
	}
}
