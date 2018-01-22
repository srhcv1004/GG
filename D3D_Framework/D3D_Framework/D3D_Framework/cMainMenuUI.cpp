#include "stdafx.h"
#include "cMainMenuUI.h"
#include "cUIButton.h"

cMainMenuUI::cMainMenuUI()
	: m_pRootUI(NULL)
{
}

cMainMenuUI::~cMainMenuUI()
{
}

void cMainMenuUI::Setup()
{
	this->SetupUI();
}

void cMainMenuUI::Release()
{
	if (m_pRootUI)
		m_pRootUI->Release();

	//D_SAFE_DELETE(m_pRootUI);
}

void cMainMenuUI::Update()
{
	if (m_pRootUI)
		m_pRootUI->Update();
}

void cMainMenuUI::Render()
{
	if (m_pRootUI)
		m_pRootUI->Render();
}

void cMainMenuUI::OnClickButton(cUIButton* pSender, E_BUTTON_TAG eButtonTag)
{
	switch (eButtonTag)
	{
		case E_BUTTON_TAG::E_TAG_INGAMESCENE:
		{
			D_SCENEMANAGER->ChangeScene("MapCastleScene");
		}
		break;

		case E_BUTTON_TAG::E_TAG_MAPTOOLSCENE:
		{
			D_SCENEMANAGER->ChangeScene("MapToolScene");
		}
		break;

		case E_BUTTON_TAG::E_TAG_OPTIONSCENE:
		{
			D_SCENEMANAGER->ChangeScene("OptionScene");
		}
		break;
	}
}

void cMainMenuUI::SetupUI()
{
	cUIButton* pBody = new cUIButton();
	pBody->Setup("tera",
		"tera",
		"tera",
		D3DXVECTOR3(D_WINSIZEX / 2.F, D_WINSIZEY / 2.F - 200.F, 0.F), 
		E_TAG_NONE);
	pBody->SetDelegate(this);
	m_pRootUI = pBody;

	cUIButton* pStart = new cUIButton();
	pStart->Setup("start",
		"start",
		"start",
		D3DXVECTOR3(0, 300, 0), 
		E_BUTTON_TAG::E_TAG_INGAMESCENE);
	pStart->SetDelegate(this);
	m_pRootUI->AddChild(pStart);

	cUIButton* pOption = new cUIButton();
	pOption->Setup("option",
		"option",
		"option",
		D3DXVECTOR3(0, 400, 0),
		E_BUTTON_TAG::E_TAG_OPTIONSCENE);
	pOption->SetDelegate(this);
	m_pRootUI->AddChild(pOption);

	cUIButton* pMaptool = new cUIButton();
	pMaptool->Setup("maptool",
		"maptool",
		"maptool",
		D3DXVECTOR3(0, 500, 0),
		E_BUTTON_TAG::E_TAG_MAPTOOLSCENE);
	pMaptool->SetDelegate(this);
	m_pRootUI->AddChild(pMaptool);
}
