/**
 * Created by rayfalling on 2020/10/26.
 * */

#pragma once

#ifndef VISREAL_I_RENDER_MANAGER_H
#define VISREAL_I_RENDER_MANAGER_H
#include <functional>
#include <thread>
#include "Screen/Screen.h"

namespace Engine::Render::Interface {
	/**
	 * An Interface class to manager windows. 
	 * Only virtual methods are provided. If you want this
	 * class be a singleton class, please inherit
	 * ISingletonObject in its divided class.
	 *
	 * @author Rayfalling
	 * */
	class IRenderManager {
		protected:
			/* Construct */
			IRenderManager() = default;

			virtual ~IRenderManager() = default;

			/* protect data member */
		protected:
			bool _fullScreen = false;
			std::function<void()> _runFunction;

		public:
			//Interface methods

			/* Init Render Device */
			virtual void Init() = 0;

			/* Static method to get only render device */
			virtual IRenderManager* GetRenderManager() = 0;

			/* Set current window size */
			virtual void SetWindowSize(Screen& screen) = 0;

			/* Set full screen mode */
			virtual void SetFullScreen(bool full) = 0;

			/* Set cursor visibility */
			virtual void SetCursor(bool visible) = 0;

			/* close current window */
			virtual void Shutdown() = 0;

			/* run window */
			virtual void Run() = 0;

			/* get full screen window size with dpi */
			virtual Screen GetFullWindowSize() = 0;

			/* get screen dpi */
			virtual float GetWindowDpi() = 0;


			// delete methods

			IRenderManager(const IRenderManager& renderManager) = delete;
			IRenderManager(IRenderManager&& renderManager) = delete;
			IRenderManager& operator=(const IRenderManager& renderManager) = delete;
			IRenderManager& operator=(IRenderManager&& renderManager) = delete;
	};
}

#endif //VISREAL_I_RENDER_MANAGER_H
