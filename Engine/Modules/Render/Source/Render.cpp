/**
 * Created by rayfalling on 2020/10/26.
 * */

#include "Render.h"

using namespace Engine::Render;

RenderManager* Renderer::GetRenderManager() {
	/* This must be initialed from construct */
	return _renderManager;
}

void Renderer::Draw() {
	Core::CoreLog::GetInstance().LogDebug(FString("Rendering Loop"));
}

Renderer::Renderer() noexcept {
}

Renderer::~Renderer() noexcept {
}
