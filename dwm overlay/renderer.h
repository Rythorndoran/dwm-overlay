#pragma once
#include <mutex>
#include<tchar.h>
#include <d3d11.h>
#pragma comment ( lib, "D3D11.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "MinHook/MinHook.h"
#pragma comment ( lib, "MinHook/libMinHook.x64.lib")
namespace overlay {
	void Initialize();
}