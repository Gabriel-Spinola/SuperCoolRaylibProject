#include "Editor.h"
#include "Camera.h"
#include "VectorHelpers.h" 

void Editor::Init() {
	SetupCamera();
}

void Editor::Tick() {
	if (IsCursorHidden()) {
		UpdateCamera(&camera_state->camera, camera_state->mode);
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		if (IsCursorHidden()) {
			EnableCursor();
		}
		else {
			DisableCursor();
		}
	}
}

void Editor::DrawWorld() {
	DrawGrid(10, 1.f);
}

void Editor::DrawUI() {
	DrawFPS(10, 10);
}

inline void Editor::SetupCamera() {
	camera_state = new CameraState();

	camera_state->camera.position = Vector3 { 0.f, 3.f, 4.f };
	camera_state->camera.target = veclib::VEC3_ZERO;
	camera_state->camera.up = veclib::VEC3_UP;
	camera_state->camera.fovy = 60.f;
	camera_state->camera.projection = CameraProjection::CAMERA_PERSPECTIVE;

	camera_state->mode = CameraMode::CAMERA_FIRST_PERSON;
}

Editor::~Editor() {
	delete camera_state;
}