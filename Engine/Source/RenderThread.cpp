/**
 * Created by rayfalling on 2020/10/26.
 * */

#include "RenderThread.h"

void Engine::InitRenderThread() {
	Renderer     = &Render::Renderer::GetInstance();
	renderThread = std::thread(RenderLoop);
}

void Engine::RenderLoop() {
	while (!ShouldRenderExit) {
		Renderer->Draw();
	}
}
