/**
 * Created by rayfalling on 2020/10/26.
 * */

#pragma once

#ifndef VISREAL_RENDER_THREAD_H
#define VISREAL_RENDER_THREAD_H

#include "Render.h"

namespace Engine {
	static Render::Renderer* Renderer;
	static std::thread RenderThread;
	/* only when render should exit then set value true */
	static bool ShouldRenderExit = false;

	/* Init render thread, logger, and other needed */
	void InitRenderThread();

	/* Terminate Render thread */
	void TerminateRenderThread();

	/* main render loop function */
	void RenderLoop();
}


#endif //VISREAL_RENDER_THREAD_H
