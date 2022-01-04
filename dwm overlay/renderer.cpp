#include "framework.h"
#include "tools.h"
#include "renderer.h"


namespace overlay {

	//文件版本: 10.0.19041.1387
	//名称: dwmcore.dll
	//大小: 3580416 字节(3496 KiB)
	//CRC32 : E845F058
	//CRC64 : 959E58158672DF18
	//SHA256 : c843d140b7ddf98dae7de2267cbd94ad1d14865fe6345f2783ae794d7bb78c67
	//SHA1 : de86f64a8e7072ea22298b850e14a9c3198f7a93
	//BLAKE2sp : 771a5be4bc2bc9894df8aa580f2d390178bc13e8979a4fd7483d87aa0d587084
	//系统版本 WINDOWS10 PRO 21H2 19044.1415

	//IDXGISwapChainDWM1即为我们需要的SwapChain，不同版本系统可能不同
	//__int64 __fastcall CD3DDevice::PresentMPO(CD3DDevice *this, struct IDXGISwapChainDWM1 *a2, __int64 a3, char a4)
	using Fn_Present = __int64(__fastcall*)(void* thisptr, IDXGISwapChain* a2, __int64 a3, char a4);

	Fn_Present Original_Present = NULL;

	static std::once_flag IsInitialized;


	static ID3D11Device* g_pd3dDevice = NULL;
	static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
	static IDXGISwapChain* g_pSwapChain = NULL;
	static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

	void ImGuiInit()
	{
		if (SUCCEEDED(g_pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice))) {
			g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
		}
		ID3D11Texture2D* RenderTargetTexture = nullptr;
		if (SUCCEEDED(g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&RenderTargetTexture)))) {
			g_pd3dDevice->CreateRenderTargetView(RenderTargetTexture, NULL, &g_mainRenderTargetView);
			if (!g_mainRenderTargetView)
				return;		
			RenderTargetTexture->Release();
		}
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		//初始化
		ImGui_ImplWin32_Init(FindWindow(L"Progman", L"Program Manager"));
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

		//设置风格
		ImGui::StyleColorsLight();

		//字体设置
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 16.0F, NULL, io.Fonts->GetGlyphRangesChineseFull());
	}

	void DrawEveryThing(IDXGISwapChain* SwapChain) {

		g_pSwapChain = SwapChain;
		std::call_once(IsInitialized, [] {ImGuiInit(); });
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello, world!");
		ImGui::Text(u8" Gitbub ：https://github.com/LoxTus ");
		ImGui::Text(u8" 中文显示测试 ");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		ImGui::GetForegroundDrawList()->AddText(ImVec2(10,10),IM_COL32_WHITE," Hello world !");
		ImGui::GetForegroundDrawList()->AddText(ImVec2(10,30), IM_COL32_WHITE, u8" 中文显示测试 ");

		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	}

	__int64 __fastcall DetourFN(void* thisptr, IDXGISwapChain* a2, __int64 a3, char a4) {
		DrawEveryThing(a2);
		return Original_Present(thisptr, a2, a3, a4);
	}

	ULONG64 GetPresentAddress()
	{
		auto instruction = pattern_scan("dwmcore.dll","E8 ?? ?? ?? ?? 8B D8 85 C0 78 ?? 41 8A D6 49 8B CF E8 ?? ?? ?? ?? EB ??");
		//instruction + instruction size + offset
		//相对地址转换绝对地址
		auto offsets = *(LONG*)((ULONG64)instruction + 1);
		auto result =(ULONG64)instruction + 5 + offsets;
		return result;
	}


	void Initialize() {
		ULONG64 PresentAddress = GetPresentAddress();
		if (!PresentAddress)
			return;
		MH_Initialize();
		MH_CreateHook(PVOID(PresentAddress), DetourFN,(LPVOID*)(&Original_Present));
		MH_EnableHook(MH_ALL_HOOKS);
	}
}
