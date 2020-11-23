/**
 * Created by rayfalling on 2020/10/26.
 * */

#include "RenderThread.h"

void Engine::InitRenderThread() {
	Renderer = &Render::Renderer::GetInstance();
	RenderThread = std::thread(RenderLoop);
}

void Engine::RenderLoop() {
	while (!ShouldRenderExit) {
		Renderer->Draw();
	}
}

void Engine::TerminateRenderThread() {
	ShouldRenderExit = true;
	RenderThread.detach();
	Renderer = nullptr;
}
