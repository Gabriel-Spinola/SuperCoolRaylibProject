#pragma once

#include "raylib.h"
#include <cstdint>

class Player;
struct CameraState;

constexpr int32_t kScreenWidth = 800;
constexpr int32_t kScreenHeight = 450;

constexpr int32_t kFrameRate = 120;
constexpr const char* kWindowTitle = "Super Cool Raylib Project";

constexpr int32_t kMaxColumns = 20;

class Game {
public:
	CameraState* camera_state;

	void Init();
	void Tick();
	void Draw();

	~Game();

private:
	Player* player;

	CameraState* InitCamera();

	void DrawUI() const;
	void DrawEnv() const;
};

