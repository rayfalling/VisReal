/**
 * Created by rayfalling on 2020/10/30.
 *
 * From Unreal4
 * */

#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#pragma once

#ifndef VISREAL_AXIS_H
#define VISREAL_AXIS_H

namespace Engine::Core {
	namespace EAxis {
		enum Type {
			None,
			X,
			Y,
			Z,
		};
	}

	// Extended axis enum for more specialized usage
	namespace EAxisList {
		enum Type {
			None = 0,
			X = 1,
			Y = 2,
			Z = 4,

			Screen = 8,
			XY = X | Y,
			XZ = X | Z,
			YZ = Y | Z,
			XYZ = X | Y | Z,
			All = XYZ | Screen,

			//alias over Axis YZ since it isn't used when the z-rotation widget is being used
			ZRotation = YZ,

			// alias over Screen since it isn't used when the 2d translate rotate widget is being used
			Rotate2D = Screen,
		};
	}
}

#endif //VISREAL_AXIS_H

#pragma clang diagnostic pop
