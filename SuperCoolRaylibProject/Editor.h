#pragma once

#include <vector>
#include <memory>
#include "raylib.h"

struct CameraState;
struct Shape {};

class Editor {
public:
	std::vector<Shape> instatiated_shapes;
	CameraState* camera_state;

	void Init();
	void Tick();
	void DrawWorld();
	void DrawUI();

	~Editor();

private:
	inline void SetupCamera();
};
