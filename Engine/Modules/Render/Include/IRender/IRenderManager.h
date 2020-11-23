/**
 * Created by rayfalling on 2020/10/26.
 * */

#pragma once

#ifndef VISREAL_I_RENDER_MANAGER_H
#define VISREAL_I_RENDER_MANAGER_H

namespace Engine::Render::Interface {
	/**
	 * An Interface class to manager render device & buffers.
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

		public:
			//Interface methods

			/* Init Render Device */
			virtual void Init() = 0;

			/* Static method to get only render device */
			virtual IRenderManager* GetRenderManager() = 0;


			// delete methods

			IRenderManager(const IRenderManager& renderManager) = delete;
			IRenderManager(IRenderManager&& renderManager) = delete;
			IRenderManager& operator=(const IRenderManager& renderManager) = delete;
			IRenderManager& operator=(IRenderManager&& renderManager) = delete;
	};
}

#endif //VISREAL_I_RENDER_MANAGER_H
