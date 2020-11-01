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
	typedef Interface::IRenderBuffer  RenderBuffer;
	typedef Interface::IRenderDevice  RenderDevice;
	typedef Interface::IRenderManager RenderManager;

	/* exposed to outer engine renderer */
	class Renderer : public Engine::Core::ISingletonObject<Renderer> {
		friend class Engine::Core::ISingletonObject<Renderer>;
		protected:
			Renderer() noexcept;
			~Renderer() noexcept override;

		private:
			Renderer(const Renderer&);
			Renderer& operator=(const Renderer&);

		private:
			/* Get appropriate render manager */
			RenderManager* _renderManager = nullptr;

		public:
			/* Get appropriate render manager */
			RenderManager* GetRenderManager();

			/* push draw command */
			void AddDrawCommand();

			/* draw frame */
			void Draw();
	};
}

#endif //VISREAL_RENDER_H
