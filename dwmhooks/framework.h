// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <tchar.h>
#include <d3d11.h>
#include <Psapi.h>
#include <process.h>
#pragma comment ( lib, "D3D11.lib")
#include"../MinHook/MinHook.h"
#pragma comment ( lib, "../MinHook/libMinHook.x64.lib")
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"