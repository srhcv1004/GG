#include "stdafx.h"
#include "cTimeManager.h"
#include "cTimer.h"

cTimeManager::cTimeManager()
	: m_pTimer(NULL)
{
}


cTimeManager::~cTimeManager()
{
}

void cTimeManager::Setup()
{
	m_pTimer = new cTimer();
	m_pTimer->Setup();
}

void cTimeManager::Update(float fLockFPS)
{
	if (m_pTimer)
		m_pTimer->Update(fLockFPS);
}

void cTimeManager::Render()
{
	HDC hdc = GetDC(g_hWnd);

	CHAR str[256] = "";
	//SetBkMode(hdc, TRANSPARENT);

#ifdef _DEBUG

	sprintf_s(str, "¡ºFPS : %d¡»", this->GetFrameRate());
	D_FONTMANAGER->DrawFontText("TimerFont", str,
		NULL,
		RectMake(0, 0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	sprintf_s(str, "¡ºWorldTime : %f¡»", this->GetWorldTime());
	D_FONTMANAGER->DrawFontText("TimerFont", str,
		NULL,
		RectMake(0, 20, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	sprintf_s(str, "¡ºElapsedTime : %f¡»", this->GetElapsedTime());
	D_FONTMANAGER->DrawFontText("TimerFont", str,
		NULL,
		RectMake(0, 40, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

#else

	sprintf_s(str, "FPS : %d", this->GetFrameRate());
	TextOut(hdc, 0, 0, str, strlen(str));

#endif // _DEBUG


	ReleaseDC(g_hWnd, hdc);
}

inline float cTimeManager::GetWorldTime()
{
	return m_pTimer->GetWorldTime();
}

inline float cTimeManager::GetElapsedTime()
{
	return m_pTimer->GetElapsedTime();
}

inline DWORD cTimeManager::GetFrameRate()
{
	return m_pTimer->GetFrameRate();
}
