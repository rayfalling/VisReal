/**
 * Created by rayfalling on 2020/11/8.
 * */

#pragma once

#ifndef vISREAL_MESH_H
#define vISREAL_MESH_H

#include "Container/TArray.h"
#include "Math/FVector.h"
#include "Object/Object.h"

namespace Engine::Core::Renderer {
	class Mesh : public Core::Object {
		public:
			/* vertexes buffer */
			TArray<FVector3> vertexes;

			/* Normals buffer */
			TArray<FVector3> Normals;
			TArray<FVector3> Targent;

		public:
			Mesh();
		private:
			/* the size of vertexes in the mesh */
			SIZE_T _size = 0;
	};
}

#endif // vISREAL_MESH_H
