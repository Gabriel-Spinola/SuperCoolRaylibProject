#pragma once

#include "raylib.h"

namespace veclib {
	constexpr const Vector3 VEC3_ONE	 = { 1.f, 1.f, 1.f };
	constexpr const Vector3 VEC3_ZERO    = { 0.f, 0.f, 0.f };

	constexpr const Vector3 VEC3_FORWARD = { 0.f, 0.f, 1.f };
	constexpr const Vector3 VEC3_RIGHT   = { 1.f, 0.f, 0.f };
	constexpr const Vector3 VEC3_UP      = { 0.f, 1.f, 0.f };
}
