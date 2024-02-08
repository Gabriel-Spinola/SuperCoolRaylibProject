#pragma once

#include "raylib.h"
#include <memory>

class Player {
public:
	Camera3D* camera = nullptr;

	Vector3 velocity;
	Transform transform;
	BoundingBox bounding_box;

	void Init(Camera3D* player_cam);
	void Tick(float delta_time);
	void Draw();

private:
	const float kMaxSpeed = 10.f;
	const float kForwardCamOffset = 3.f;
	const float kUpCamOffset = -1.5f;

	void HandleInput(float delta_time);

public: 
	~Player();
};

