#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <mmsystem.h>

#include <iostream>
#include <ctime>
#include <cmath>
#include <cassert>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <queue>

#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9core.h>
#include <d3dx9anim.h>

#include "cDeviceManager.h"
#include "cKeyManager.h"
#include "cRndManager.h"
#include "cTimeManager.h"
#include "cSceneManager.h"
#include "cSoundManager.h"
#include "cSpriteManager.h"
#include "cFontManager.h"
#include "cAseLoadManager.h"
#include "cTexMtlManager.h"
#include "cItemManager.h"
#include "utils.h"

// ----------------------------------------------------------------------------------------------------
#define D_WINNAME											(LPTSTR)(TEXT("D3DGame"))
#define D_WINSTYLE											WS_CAPTION | WS_SYSMENU
#define D_WINSTARTX											50
#define D_WINSTARTY											50
#define D_WINSIZEX											1024
#define D_WINSIZEY											768

#define D_DEVICE											cDeviceManager::GetSingleton()->GetDevice()
#define D_DEVICEMANAGER										cDeviceManager::GetSingleton()
#define D_KEYMANAGER										cKeyManager::GetSingleton()
#define D_RNDMANAGER										cRndManager::GetSingleton()
#define D_TIMEMANAGER										cTimeManager::GetSingleton()
#define D_SCENEMANAGER										cSceneManager::GetSingleton()
#define D_SOUNDMANAGER										cSoundManager::GetSingleton()
#define D_SPRITEMANAGER										cSpriteManager::GetSingleton()
#define D_FONTMANAGER										cFontManager::GetSingleton()
#define D_ASELOADMANAGER									cAseLoadManager::GetSingleton()
#define D_TEXMTLMANAGER										cTexMtlManager::GetSingleton()
#define D_ITEMMANAGER										cItemManager::GetSingleton()

#define D_SAFE_RELEASE(p)									if(p){(p)->Release();(p)=NULL;}
#define D_SAFE_DELETE(p)									if(p){delete(p);(p)=NULL;}
#define D_SAFE_DELETE_ARR(p)								if(p){delete[](p);(p)=NULL;}
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
#define D_SYNTHESIZE(varType, varName, funcName) \
	protected: \
		varType varName; \
	public: \
		varType Get##funcName(){return varName;} \
		void Set##funcName(varType var){varName = var;}

#define D_SYNTHESIZE_REF(varType, varName, funcName) \
	protected: \
		varType varName; \
	public: \
		varType& Get##funcName(){return varName;} \
		void Set##funcName(varType& var){varName = var;}
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
extern HINSTANCE											g_hInstance;
extern HWND													g_hWnd;
extern POINT												g_ptMouse;
extern FLOAT												g_fWheelDelta;
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
#include "commonST.h"
#include "commonEN.h"
#include "commonFC.h"
#include "commonDF.h"
// ----------------------------------------------------------------------------------------------------