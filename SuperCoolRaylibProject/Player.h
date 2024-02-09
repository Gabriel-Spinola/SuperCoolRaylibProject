#pragma once

#include "raylib.h"
#include <memory>

struct CameraState;

class Player {
public:
	std::shared_ptr<CameraState> camera_state;

	Vector3 velocity;
	Transform transform;
	BoundingBox bounding_box;

	void Init(std::shared_ptr<CameraState> player_cam);
	void Tick(float delta_time);
	void Draw();

	void adjustPlayerOnCollision(BoundingBox* box2);

private:
	const float kMaxSpeed = 10.f;
	const float kForwardCamOffset = 3.f;
	const float kUpCamOffset = -1.5f;
	const float kCollisionOffset = .1f;

	void HandleInput(float delta_time);
	void CalculateBoundingBox();
};

