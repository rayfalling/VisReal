/**
 * Created by rayfalling on 2020/11/8.
 * */

#pragma once

#ifndef VISREAL_MESH_H
#define VISREAL_MESH_H

#include "Container/TArray.h"
#include "Math/FVector.h"
#include "Object/Object.h"

namespace Engine::Core::Renderer {
	class Mesh : public Object {
		public:
			/* vertexes buffer */
			TArray<Math::FVector3> Vertexes;

			/* Normals buffer */
			TArray<Math::FVector3> Normals;
			TArray<Math::FVector3> Tangents;

		public:
			Mesh();
		private:
			/* the size of vertexes in the mesh */
			SIZE_T _size = 0;
	};
}

#endif // VISREAL_MESH_H
