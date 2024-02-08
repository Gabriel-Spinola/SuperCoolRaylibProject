#include "Player.h"
#include "VectorHelpers.h"
#include "raylib_operator_overloads.hpp"

void Player::Init(Camera3D* player_cam) {
	camera = player_cam;

	transform.translation = Vector3 { 0.f, 5.f, 0.f };
	transform.rotation = Quaternion{};
	transform.scale = Vector3 { 1.f, 3.f, 1.f };
}

void Player::Tick(float delta_time) {
	using namespace veclib;

	// Damping
	velocity *= 1.f / (1.f + delta_time * 2);

	// Camera movement
	camera->position += velocity * delta_time;

	// Camera Position
	camera->target = camera->position + (VEC3_FORWARD * kForwardCamOffset + VEC3_UP * kUpCamOffset);

	// Assign camera calculations to tranform
	transform.translation = camera->target;

	HandleInput(delta_time);
}

void Player::Draw() {
	DrawCubeV(transform.translation, transform.scale, PURPLE);
}

void Player::HandleInput(float delta_time) {
	if (IsKeyDown(KEY_W)) velocity += veclib::VEC3_FORWARD * delta_time * kMaxSpeed;
	if (IsKeyDown(KEY_S)) velocity -= veclib::VEC3_FORWARD * delta_time * kMaxSpeed;

	if (IsKeyDown(KEY_D)) velocity -= veclib::VEC3_RIGHT * delta_time * kMaxSpeed;
	if (IsKeyDown(KEY_A)) velocity += veclib::VEC3_RIGHT * delta_time * kMaxSpeed;
}

// FIXME - Might be causing a Double Free with the camera pointer
Player::~Player() {
	if (camera == nullptr) {
		return;
	}

	delete camera;
}
