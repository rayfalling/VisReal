/**
 * Created by rayfalling on 2020/10/26.
 * */

#pragma once

#ifndef VISREAL_I_RENDER_DEVICE_H
#define VISREAL_I_RENDER_DEVICE_H

namespace Engine::Render::Interface {
	/**
	 * An Interface class to create render device.
	 * Only virtual methods are provided. If you want this
	 * class be a singleton class, please inherit
	 * ISingletonObject in its divided class.
	 *
	 * @author Rayfalling
	 * */
	class IRenderDevice {
		protected:
			/* Construct */
			inline IRenderDevice() = default;

		public:
			/* Init Render Device */
			virtual void Init() = 0;

			/* Static method to get only render device */
			virtual IRenderDevice GetRenderDevice() = 0;

			/* Set main window size */
			virtual void SetWindowSize() = 0;
	};
}

#endif //VISREAL_I_RENDER_DEVICE_H
