#include "Player.h"
#include "VectorHelpers.h"
#include "raylib_operator_overloads.hpp"
#include "Camera.h"
#include <stdio.h>

void Player::Init(std::shared_ptr<CameraState> player_cam) {
	camera_state = player_cam;

	transform.translation = Vector3 { 0.f, 3.f, 0.f };
	transform.rotation = Quaternion{};
	transform.scale = Vector3 { 1.f, 3.f, 1.f };
}

void Player::Tick(float delta_time) {
	using namespace veclib;

	// Damping
	velocity *= 1.f / (1.f + delta_time * 2);

	// Movement
	transform.translation += velocity * delta_time;

	// Offset camera to be behind the player
	camera_state->camera.position = transform.translation + (VEC3_FORWARD * kForwardCamOffset + VEC3_UP * kUpCamOffset);

	Vector2 mousePos = GetMousePosition();
	Vector2 targetPos = GetWorldToScreen(transform.translation, camera_state->camera);
	
	//mousePos.x -= targetPos.x;
	//mousePos.y -= targetPos.y;

	// Assign camera target to player;
	camera_state->camera.target = transform.translation;
		
	//UpdateCamera(&camera_state->camera, camera_state->mode);
	UpdateCameraPro(&camera_state->camera, VEC3_ZERO, VEC3_ZERO, 1.f);

	HandleInput(delta_time);
	CalculateBoundingBox();
}

void Player::Draw() {
	DrawCubeV(transform.translation, transform.scale, PURPLE);
}

inline void Player::AdjustPlayerOnCollision(BoundingBox& box2) {
	if (bounding_box.max.x > box2.max.x) {
		velocity.x = Clamp(velocity.x, kCollisionOffset, kMaxSpeed);
	}

	if (bounding_box.max.x < box2.max.x) {
		velocity.x = Clamp(velocity.x, -kMaxSpeed, -kCollisionOffset);
	}

	if (bounding_box.max.z > box2.max.z) {
		velocity.z = Clamp(velocity.z, kCollisionOffset, kMaxSpeed);
	}

	if (bounding_box.max.z < box2.max.z) {
		velocity.z = Clamp(velocity.z, -kMaxSpeed, -kCollisionOffset);
	}
}

void Player::HandleInput(float delta_time) {
	if (IsKeyDown(KEY_W)) {
		velocity += veclib::VEC3_FORWARD * delta_time * kMaxSpeed;;
	}

	if (IsKeyDown(KEY_S)) {
		velocity -= veclib::VEC3_FORWARD * delta_time * kMaxSpeed;
	}

	if (IsKeyDown(KEY_D)) {
		velocity -= veclib::VEC3_RIGHT * delta_time * kMaxSpeed;
	}

	if (IsKeyDown(KEY_A)) {
		velocity += veclib::VEC3_RIGHT * delta_time * kMaxSpeed;
	}
}

void Player::CalculateBoundingBox() {
	bounding_box = BoundingBox{};

	bounding_box.min = Vector3 {
		transform.translation.x - transform.scale.x / 2,
		transform.translation.y - transform.scale.y / 2,
		transform.translation.z - transform.scale.z / 2,
	};

	bounding_box.max = Vector3 {
		transform.translation.x + transform.scale.x / 2,
		transform.translation.y + transform.scale.y / 2,
		transform.translation.z + transform.scale.z / 2,
	};
}
