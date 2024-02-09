#pragma once

#include "raylib.h"
#include <memory>

struct CameraState {
	Camera3D camera;
	CameraMode mode;
};