/**
 * Created by rayfalling on 2020/10/26.
 * */

#pragma once

#ifndef VISREAL_RENDER_H
#define VISREAL_RENDER_H

#include "Object/ISingletonObject.h"
#include "IRender/IRenderDevice.h"
#include "IRender/IRenderBuffer.h"
#include "IRender/IRenderManager.h"

namespace Engine::Render {
	typedef Interface::IRenderBuffer RenderBuffer;
	typedef Interface::IRenderDevice RenderDevice;
	typedef Interface::IRenderManager RenderManager;

	/* exposed to outer engine renderer */
	class Renderer final : public Core::ISingletonObject<Renderer> {
		// ReSharper disable once CppRedundantQualifier
		friend class Engine::Core::ISingletonObject<Renderer>;
		protected:
			Renderer() noexcept;
			~Renderer() noexcept override;

		public:
			Renderer(const Renderer&) = delete;
			Renderer(const Renderer&&) = delete;
			Renderer& operator=(const Renderer&) = delete;
			Renderer& operator=(const Renderer&&) = delete;

		private:
			/* Get appropriate render manager */
			RenderManager* _renderManager = nullptr;

		public:
			/* Get appropriate render manager */
			[[nodiscard]] RenderManager* GetRenderManager() const;

			/* push draw command */
			void AddDrawCommand();

			/* draw frame */
			void Draw();
	};
}

#endif //VISREAL_RENDER_H
