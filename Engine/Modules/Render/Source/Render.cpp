/**
 * Created by rayfalling on 2020/10/26.
 * */

#include "Render.h"
#include "DirectX/DxWindowManager.h"

using namespace Engine::Render;

RenderManager* Renderer::GetRenderManager() const {
	return _renderManager;
}

void Renderer::Draw() {
	Core::CoreLog::GetInstance().LogInfo(FString("Rendering Loop"));
}

Renderer::Renderer() noexcept {
	_renderManager = DirectX::DxWindowManager::GetInstancePtr();
	_renderManager->Init();
	_renderManager->RegisterEvent();
}

Renderer::~Renderer() noexcept {
	_renderManager->Shutdown();
	_renderManager = nullptr;
}
