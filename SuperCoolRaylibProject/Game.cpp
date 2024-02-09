#include "Game.h"
#include "Player.h"
#include "VectorHelpers.h"
#include "Camera.h"

// ANCHOR - Public Methods
void Game::Init() {
	player = new Player();

	InitWindow(kScreenWidth, kScreenHeight, kWindowTitle);

	SetTargetFPS(kFrameRate);
	HideCursor();

	camera_state = InitCamera();
	player->Init(camera_state);
}

void Game::Tick() {
	player->Tick(GetFrameTime());
}

void Game::Draw() {
	BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(camera_state->camera);
			player->Draw();

			DrawEnv();
		EndMode3D();

		DrawUI();
	EndDrawing();
}

// ANCHOR - Private Methods
std::shared_ptr<CameraState> Game::InitCamera() {
	auto state = std::make_shared<CameraState>();

	state->camera.position = Vector3{ 0.f, 3.f, 4.f };
	state->camera.target = veclib::VEC3_ZERO;
	state->camera.up = veclib::VEC3_UP;
	state->camera.fovy = 60;
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
