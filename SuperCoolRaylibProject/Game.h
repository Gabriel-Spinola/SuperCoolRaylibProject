#pragma once

#include "raylib.h"
#include <cstdint>
#include <memory>
#include "Editor.h"

class Player;
struct CameraState;

constexpr int32_t kScreenWidth = 800;
constexpr int32_t kScreenHeight = 450;

constexpr int32_t kFrameRate = 120;
constexpr const char* kWindowTitle = "Super Cool Raylib Project";

constexpr int32_t kMaxColumns = 20;

class Game {
public:
	std::shared_ptr<CameraState> camera_state;
	std::unique_ptr<Editor> editor;

	void Init();
	void Tick();
	void Draw() const;

	~Game();

private:
	Player* player;
	std::shared_ptr<CameraState> InitCamera();

	bool is_on_editing_mode = false;

	void DrawUI() const;
	void DrawEnv() const;
};

