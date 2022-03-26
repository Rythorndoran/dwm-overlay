#pragma once
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <WinUser.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <d3d11.h>
#include <Psapi.h>
#include <process.h>
#include <dxgi.h>
#include <dxgi1_5.h>
#include <iostream>
#pragma comment ( lib, "D3D11.lib")
#include"../MinHook/MinHook.h"
#pragma comment ( lib, "../MinHook/libMinHook.x64.lib")
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"

typedef void(*CallBackptr)(void);
namespace Hooks
{
	DWORD64 FindPattern(const char* szModule, BYTE* bMask, const char* szMask);
	BOOL bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	int GetOsBuildNumber();
	bool Install(CallBackptr callbackfun);
	void DemoDraw();
}

