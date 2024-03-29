/**
 * Created by rayfalling on 2020/11/23.
 * */

#include "DirectX/DxWindowManager.h"

#include "EventLoop.h"
#include "Marco/Constant.h"

using namespace Engine::Render::DirectX;

void DxWindowManager::Init() {
	const auto dpi = GetWindowDpi();
	Core::CoreLog::GetInstance().LogInfo(Core::Types::FString::Format("Current display DPI scale is {}.", dpi));
	Screen screen(1280, 720, 0, 0, dpi);
	Core::CoreLog::GetInstance().LogInfo(Core::Types::FString::Format("Set window size to {}x{}.", screen.GetWidth(), screen.GetHeight()));
	_screen = screen;
	CreateAppWindow(screen);
}

void DxWindowManager::RegisterEvent() {
	_runFunction = &DxWindowManager::MessageLoop;
	Event::EventLoop::GetInstance().RegisterEvent(_runFunction);
}

void DxWindowManager::SetWindowSize(Screen& screen) {
	SetWindowLong(_hwnd, GWL_STYLE, WS_BORDER);
	SetWindowPos(_hwnd, HWND_TOPMOST, 0, 0, static_cast<int>(screen.GetWidth()), static_cast<int>(screen.GetHeight()), SWP_SHOWWINDOW);
	Core::CoreLog::GetInstance().LogInfo(Core::Types::FString::Format("Set window size to {}x{}.", screen.GetWidth(), screen.GetHeight()));
}

FORCEINLINE void DxWindowManager::SetCursor(const bool visible) {
	ShowCursor(visible);
}

void DxWindowManager::SetFullScreen(const bool full) {
	_fullScreen = full;
}

Engine::Render::Interface::IRenderManager* DxWindowManager::GetRenderManager() {
	return this;
}

Engine::Render::Screen& DxWindowManager::GetScreen() {
	return _screen;
}

void DxWindowManager::Shutdown() {
	Event::EventLoop::GetInstance().UnregisterEvent(_runFunction);

	DestroyWindow(_hwnd);
	_hwnd = nullptr;
	UnregisterClass(Core::C_APPLICATION_NAME.GetData(), _hInstance);
	_hInstance = nullptr;
}

Engine::Render::Screen DxWindowManager::GetFullWindowSize() {
	Screen      screen;
	auto* const hdc = GetDC(nullptr);
	screen.SetRawWidth(GetDeviceCaps(hdc, DESKTOPHORZRES));
	screen.SetRawHeight(GetDeviceCaps(hdc, DESKTOPVERTRES));
	screen.SetDpi(static_cast<float>(GetDeviceCaps(hdc, DESKTOPHORZRES)) / static_cast<float>(GetSystemMetrics(SM_CXSCREEN)));
	ReleaseDC(nullptr, hdc);
	return screen;
}

float DxWindowManager::GetWindowDpi() {
	auto* const hdc = GetDC(nullptr);
	const auto  dpi = static_cast<float>(GetDeviceCaps(hdc, DESKTOPHORZRES)) / static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
	ReleaseDC(nullptr, hdc);
	return dpi;
}

DxWindowManager::DxWindowManager() = default;

void DxWindowManager::CreateAppWindow(Screen& screen) {
	SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
	WNDCLASSEX window;

	// get module instance
	_hInstance = GetModuleHandle(nullptr);

	// set window
	window.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	window.lpfnWndProc = MessageProcess;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = _hInstance;
	window.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	window.hIconSm = window.hIcon;
	window.hCursor = LoadCursor(nullptr, IDC_ARROW);
	window.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	window.lpszMenuName = nullptr;
	window.lpszClassName = Core::C_APPLICATION_NAME.GetData();
	window.cbSize = sizeof(WNDCLASSEX);

	// register
	RegisterClassEx(&window);

	// get system screen size
	const uint32 screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const uint32 screenHeight = GetSystemMetrics(SM_CYSCREEN);

	screen.SetPositionX(static_cast<int32>(screenWidth / 2 - screen.GetWidth() / 2));
	screen.SetPositionY(static_cast<int32>(screenHeight / 2 - screen.GetHeight() / 2));

	// create window
	_hwnd = CreateWindow(
		Core::C_APPLICATION_NAME.GetData(), Core::C_APPLICATION_NAME.GetData(), WS_OVERLAPPEDWINDOW,
		screen.GetPositionX(), screen.GetPositionY(), screen.GetWidth(), screen.GetHeight(),
		nullptr, nullptr, _hInstance, nullptr
	);

	FullScreen();

	ShowWindow(_hwnd, SW_SHOW);
	SetForegroundWindow(_hwnd);
	SetFocus(_hwnd);
	Core::CoreLog::GetInstance().LogInfo(Core::Types::FString("Window created."));
}

void DxWindowManager::SetDpiUnaware() {
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_UNAWARE);
}

void DxWindowManager::SetDpiAware() {
	SetProcessDPIAware();
}

void DxWindowManager::FullScreen() {
	if (_hwnd == nullptr) return;
	if (_fullScreen) {
		auto full = GetFullWindowSize();
		SetWindowLongPtr(_hwnd, GWL_STYLE, WS_POPUP);
		SetWindowPos(
			_hwnd, HWND_TOP, static_cast<int>(full.GetPositionX()), static_cast<int>(full.GetPositionY()),
			static_cast<int>(full.GetWidth()), static_cast<int>(full.GetHeight()),SWP_SHOWWINDOW
		);
		Core::CoreLog::GetInstance().LogInfo(Core::Types::FString("Window set to full screen"));


	} else {
		SetWindowLongPtr(_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(
			_hwnd, HWND_TOP, static_cast<int>(_screen.GetPositionX()), static_cast<int>(_screen.GetPositionY()),
			static_cast<int>(_screen.GetWidth()), static_cast<int>(_screen.GetHeight()), SWP_SHOWWINDOW
		);
		Core::CoreLog::GetInstance().LogInfo(Core::Types::FString("Window set to normal"));

	}
}

void DxWindowManager::MessageLoop() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT) {
		exit(0);
	}
}

LRESULT MessageProcess(HWND hwnd, const UINT uMessage, const WPARAM wParam, const LPARAM lParam) {
	switch (uMessage) {
		case WM_SIZE:
			DxWindowManager::GetInstance().GetScreen().SetWidth(LOWORD(lParam));
			DxWindowManager::GetInstance().GetScreen().SetHeight(HIWORD(lParam));
			return 0;
		case WM_MOVE:
			const auto points = MAKEPOINTS(lParam);
			DxWindowManager::GetInstance().GetScreen().SetPosition(points.x, points.y);
			return 0;
		case WM_DESTROY:
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		default:
			/*TODO add input system*/
			return DefWindowProc(hwnd, uMessage, wParam, lParam);
	}
}
