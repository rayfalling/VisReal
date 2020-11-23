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

namespace Engine::Render::DirectX {
	class DxWindowManager : public Core::ISingletonObject<DxWindowManager>, public Interface::IRenderManager {
		public:
			void Init() override;

		private:
			DxWindowManager();
	};
}
#endif
