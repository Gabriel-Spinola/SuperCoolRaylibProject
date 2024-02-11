#include "Game.h"
#include "Player.h"
#include "VectorHelpers.h"
#include "Camera.h"

// ANCHOR - Public Methods
void Game::Init() {
	player = new Player();
	editor = std::make_unique<Editor>();

	InitWindow(kScreenWidth, kScreenHeight, kWindowTitle);

	SetTargetFPS(kFrameRate);
	DisableCursor();

	camera_state = InitCamera();
	player->Init(camera_state);
	editor->Init();
}

void Game::Tick() {
	camera_state->is_enable = !is_on_editing_mode;
	editor->camera_state->is_enable = is_on_editing_mode;

	if (IsKeyPressed(KEY_LEFT_ALT)) {
		is_on_editing_mode = !is_on_editing_mode;
		DisableCursor();

		if (is_on_editing_mode) {
			EnableCursor();
		}
	}

	if (is_on_editing_mode) {
		editor->Tick();

		return;
	}

	player->Tick(GetFrameTime());
}

void Game::Draw() const {
	BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(is_on_editing_mode ? editor->camera_state->camera : camera_state->camera);
			player->Draw();
			DrawEnv();

			if (is_on_editing_mode) {
				editor->DrawWorld();
			}
		EndMode3D();

		if (is_on_editing_mode) {
			editor->DrawUI();
		}

		DrawUI();
	EndDrawing();
}

// ANCHOR - Private Methods
std::shared_ptr<CameraState> Game::InitCamera() {
	auto state = std::make_shared<CameraState>();

	state->camera.position = Vector3{ 0.f, 3.f, 4.f };
	state->camera.target = veclib::VEC3_ZERO;
	state->camera.up = veclib::VEC3_UP;
	state->camera.fovy = 60.f;
	state->camera.projection = CameraProjection::CAMERA_PERSPECTIVE;

	state->mode = CameraMode::CAMERA_FIRST_PERSON;

	return state;
}

void Game::DrawUI() const {
	DrawFPS(10, 10);
}

void Game::DrawEnv() const {
	DrawPlane(Vector3 { 0, 0, 0 }, Vector2 { 32, 32 }, LIGHTGRAY); // Draw ground

	DrawCube(Vector3 { -16, 2, 0 }, 1, 5, 32, BLUE);     // Draw a blue wall
	DrawCube(Vector3 { 16, 2, 0 }, 1, 5, 32, LIME);      // Draw a green wall
	DrawCube(Vector3 { 0, 2, 16 }, 32, 5, 1, GOLD);      // Draw a yellow wall
}

Game::~Game() {
	delete player;
}
