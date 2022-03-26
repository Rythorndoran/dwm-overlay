#include"Hooks.h"
typedef __int64(__fastcall* Present_1809)(void* thisptr, __int64 a2, unsigned int a3, unsigned int a4, __int64 a5);
typedef __int64(__fastcall* Present_1909)(void* thisptr, __int64 a2, unsigned int a3, unsigned int a4, __int64 a5);
typedef __int64(__fastcall* Present_2004)(void* thisptr, IDXGISwapChain* a2);
typedef __int64(__fastcall* Present_20H2)(void* thisptr, IDXGISwapChain* a2, __int64 a3, char a4);
typedef __int64(__fastcall* Present_21H2)(void* thisptr, IDXGISwapChain* a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6);
Present_1809 oPresent_1809 = nullptr;
Present_1909 oPresent_1909 = nullptr;
Present_2004 oPresent_2004 = nullptr;
Present_20H2 oPresent_20H2 = nullptr;
Present_21H2 oPresent_21H2 = nullptr;

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
CallBackptr funptr = nullptr;

bool ImGuiInit()
{
	if (SUCCEEDED(g_pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice)))
	{
		g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
	}
	else
		return false;
	ID3D11Texture2D* RenderTargetTexture = nullptr;
	if (SUCCEEDED(g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&RenderTargetTexture))))
	{
		g_pd3dDevice->CreateRenderTargetView(RenderTargetTexture, NULL, &g_mainRenderTargetView);
		if (!g_mainRenderTargetView)
		{
			return false;
		}
		RenderTargetTexture->Release();
	}
	else
		return false;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsLight();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 16.0F, NULL, io.Fonts->GetGlyphRangesChineseFull());
	auto vStyle = &ImGui::GetStyle();
	vStyle->GrabRounding = 10.0f;
	vStyle->WindowRounding = 10.0f;
	vStyle->TabRounding = 10.0f;
	vStyle->FrameRounding = 10.0f;
	vStyle->PopupRounding = 10.0f;
	vStyle->ChildRounding = 10.0f;
	ImGui_ImplWin32_Init(FindWindow(L"Progman", L"Program Manager"));
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	return true;
}

__int64 __fastcall HKPresent_1909(void* thisptr, __int64 a2, unsigned int a3, unsigned int a4, __int64 a5)
{
	static bool IsInitialize = false;
	if (!IsInitialize)
	{
		g_pSwapChain = *((IDXGISwapChain**)thisptr + 53);
		IsInitialize = ImGuiInit();
	}
	else
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		funptr();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent_1909(thisptr, a2, a3, a4, a5);
}

__int64 __fastcall HKPresent_1809(void* thisptr, __int64 a2, unsigned int a3, unsigned int a4, __int64 a5)
{
	static bool IsInitialize = false;
	if (!IsInitialize)
	{
		g_pSwapChain = *((IDXGISwapChain**)thisptr + 53);
		IsInitialize = ImGuiInit();
	}
	else
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		funptr();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent_1809(thisptr, a2, a3, a4, a5);
}

__int64 __fastcall HKPresent_2004(void* thisptr, IDXGISwapChain* a2)
{
	static bool IsInitialize = false;
	if (!IsInitialize)
	{
		g_pSwapChain = a2;
		IsInitialize = ImGuiInit();
	}
	else
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		funptr();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent_2004(thisptr, a2);
}

__int64 __fastcall HKPresent_20H2(void* thisptr, IDXGISwapChain* a2, __int64 a3, char a4)
{
	static bool IsInitialize = false;
	if (!IsInitialize)
	{
		g_pSwapChain = a2;
		IsInitialize = ImGuiInit();
	}
	else
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		funptr();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent_20H2(thisptr, a2, a3, a4);
}

__int64 __fastcall HKPresent_21H2(void* thisptr, IDXGISwapChain* a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6)
{
	static bool IsInitialize = false;
	if (!IsInitialize)
	{
		g_pSwapChain = a2;
		IsInitialize = ImGuiInit();
	}
	else
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		funptr();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent_21H2(thisptr,a2, a3, a4, a5, a6);
}

	int Hooks::GetOsBuildNumber()
	{
		uintptr_t PEB;
		int OsBuildNumber;
#ifdef _WIN64
		PEB = __readgsqword(0x60);
		OsBuildNumber = *((INT*)(PEB + 0x120));
#else
		PEB = __readfsdword(0x30);
		OsBuildNumber = *((INT*)(PEB + 0xAC));
#endif 
		return OsBuildNumber;
	}

	BOOL Hooks::bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
		{
			if (*szMask == 'x' && *pData != *bMask)
				return FALSE;
		}
		return (*szMask) == NULL;
	}

	DWORD64 Hooks::FindPattern(const char* szModule, BYTE* bMask, const char* szMask)
	{
		MODULEINFO mi{ };
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &mi, sizeof(mi));

		DWORD64 dwBaseAddress = DWORD64(mi.lpBaseOfDll);
		const auto dwModuleSize = mi.SizeOfImage;

		for (auto i = 0ul; i < dwModuleSize; i++)
		{
			if (bDataCompare(PBYTE(dwBaseAddress + i), bMask, szMask))
				return DWORD64(dwBaseAddress + i);
		}
		return NULL;
	}

	bool Hooks::Install(CallBackptr callbackfun)
	{
		PVOID Present = nullptr;
		PVOID HKPresent = nullptr;
		PVOID* oPresent = nullptr;
		if (!callbackfun)
			return false;
		funptr = callbackfun;
		if (!(MH_Initialize() == MH_OK)){
			return false;
		}
		int OSBulidNumber = GetOsBuildNumber();
		if (OSBulidNumber == 22000)//win11 dev 21h2
		{
			 Present = (PVOID)FindPattern("dwmcore.dll",
				PBYTE("\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x50\x8B\x99"),
				"xxxx?xxxx?xxxxxxx");
			 HKPresent = &HKPresent_21H2;
			 oPresent = reinterpret_cast<PVOID*>(&oPresent_21H2);
		}
		else if (OSBulidNumber == 19043 || OSBulidNumber == 19042)//21h1 20h2
		{
			  Present = (PVOID)FindPattern("dwmcore.dll",
				  PBYTE("\x4C\x8B\xDC\x49\x89\x5B\x00\x49\x89\x6B\x00\x49\x89\x73\x00\x57\x48\x83\xEC\x50\x8B\x99\x00\x00\x00\x00\x41\x8B\xE9\x48\x8B\xF2\x48\x8B\xF9\x85\xDB\x0F\x88"),
				  "xxxxxx?xxx?xxx?xxxxxxx????xxxxxxxxxxxxx");

			 HKPresent = &HKPresent_20H2;
			 oPresent = reinterpret_cast<PVOID*>(&oPresent_20H2);
		}
		else if (OSBulidNumber == 19041)
		{
			Present = (PVOID)FindPattern("dwmcore.dll", PBYTE("\x4C\x8B\xDC\x49\x89\x5B\x00\x49\x89\x73\x00\x57\x48\x83\xEC\x60\x8B\x99\x00\x00\x00\x00\x48\x8B\xF2\x48\x8B\xF9\x85\xDB\x0F\x88\x00\x00\x00\x00\x48\x8B\x89\x00\x00\x00\x00\x48\x8B\x01"), "xxxxxx?xxx?xxxxxxx????xxxxxxxxxx????xxx????xxx");
			 HKPresent = &HKPresent_2004;
			 oPresent = reinterpret_cast<PVOID*>(&oPresent_2004);
		}
		else if (OSBulidNumber == 18362 || OSBulidNumber == 18363)
		{
			 Present = (PVOID)FindPattern("dwmcore.dll",
				PBYTE("\x40\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\xC8\x01\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00\x48\x8B\xBD\x00\x00\x00\x00\x48\x8D\x45\x00\x48\x89\x45"),
				"xxxxxxxxxxxxxxxxx????xxxxxxxxxx????xxxxxx????xxx????xxxxxxx");
			 HKPresent = &HKPresent_1909;
			 oPresent = reinterpret_cast<PVOID*>(&oPresent_1909);
		}
		else if (OSBulidNumber == 17763)
		{
			Present = (PVOID)FindPattern("dwmcore.dll", PBYTE("\x40\x55\x53\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\xC8\x01\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x85\x00\x00\x00\x00"), "xxxxxxxxxxxxxxxxx????xxxxxxxxxx????xxxxxx????");
			HKPresent = &HKPresent_1809;
			oPresent = reinterpret_cast<PVOID*>(&oPresent_1809);
		}
		char text[100];
		sprintf_s(text, "系统版本：%d\n函数地址:%llu", OSBulidNumber,(UINT64)Present);
		MessageBoxA(NULL, text, "", MB_ICONINFORMATION);
		MH_CreateHook(PVOID(Present), HKPresent, oPresent);
		MH_EnableHook(MH_ALL_HOOKS);
		return true;
	}

	void Hooks::DemoDraw()
	{
		static short CurrentStates, LastStates;
		ImGuiIO& io = ImGui::GetIO();
		CurrentStates = GetAsyncKeyState(1);
		//写的丑但是确实有用
		if (CurrentStates) {
			LastStates = CurrentStates;
			//这里是按下左键
			io.MouseDown[0] = true;
		}
		else if (LastStates) {
			LastStates = 0;
			//弹开
			io.MouseDown[0] = false;
		}

		ImGui::GetOverlayDrawList()->AddRect(ImVec2(200, 200), ImVec2(400, 400), ImGui::ColorConvertFloat4ToU32(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)));
		static bool Checkbox = true;
		static ImVec4 color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		if (true)
		{
			static float f = 0.0f;
			static int counter = 0;
			static float flRainbow;
			ImGui::DrawRainbowLine(ImVec2(0, 2), ImVec2(float(1920), float(2)), 3, 0.002f, flRainbow);
			ImGui::Begin("Hello, world!");
			ImGui::DrawRectRainbow(0.002f);
			ImGui::Checkbox("Checkbox", &Checkbox);
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&color);
			if (ImGui::Button("Button"))
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
	}
