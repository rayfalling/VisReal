/**
 * Created by rayfalling on 2020/8/29.
 *
 * DirectX window manager
 * Singleton mode to avoid multi window
 * */

#pragma once

#ifndef VISREAL_DX_WINDOW_MANAGER_H
#define VISREAL_DX_WINDOW_MANAGER_H

#include "IRender/IRenderManager.h"
#include "Object/ISingletonObject.h"
#include "Platform/PlatformTypes.h"

/* accurate build */
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Screen/Screen.h"

namespace Engine::Render::DirectX {
	class DxWindowManager final : public Core::ISingletonObject<DxWindowManager>, public Interface::IRenderManager {
		// ReSharper disable once CppRedundantQualifier
		friend class Engine::Core::ISingletonObject<DxWindowManager>;

		public:
			void Init() override;

			void RegisterEvent() override;

			void SetWindowSize(Screen& screen) override;

			void SetCursor(bool visible) override;

			void SetFullScreen(bool full) override;

			void Shutdown() override;

			Screen GetFullWindowSize() override;

			float GetWindowDpi() override;

			IRenderManager* GetRenderManager() override;

			Screen& GetScreen();

			/* private methods */
		private:
			DxWindowManager();

			void CreateAppWindow(Screen& screen);

			/* set process unaware dpi scale */
			static void SetDpiUnaware();
			/* set process aware dpi scale */
			static void SetDpiAware();

		protected:
			/* Set window size and position */
			void FullScreen();

		public:
			/* window message loop */
			static void MessageLoop();

			/* data member */
		private:
			HINSTANCE _hInstance{};
			HWND _hwnd{};
			Screen _screen;

			/* use for stop message loop */
			bool _quit = false;
	};
}

static LRESULT CALLBACK MessageProcess(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

#endif
