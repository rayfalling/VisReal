//
// Created by rayfalling on 2020/8/29.
//
#pragma once

#ifndef VISREAL_OBJECT_H
#define VISREAL_OBJECT_H

#include "Container/FString.h"
#include "EngineCoreExport.generate.h"
#include "Hash/Hash.h"

namespace Engine::Core {
	using namespace Types;

	/* Base Object Class */
	class ENGINE_CORE_EXPORTS Object {
		protected:
			FString _name;
			uint64 _id;

		private:
			inline static std::atomic<uint64> _currentId{0};

		public:
			Object() noexcept : _id{_currentId++} {
			}

			Object(const Object& object) = default;
			Object(Object&& object) = default;
			Object& operator=(Object&& object) noexcept = default;
			Object& operator=(const Object& object) noexcept = default;
			virtual ~Object() = default;

			virtual uint64 GetHashCode() const {
				return FHash::Hash(this);
			}

			virtual FString GetName() const {
				return _name;
			}
	};
}

#endif //VISREAL_OBJECT_H
