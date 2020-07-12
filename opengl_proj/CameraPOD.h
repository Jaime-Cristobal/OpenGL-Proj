#pragma once


enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

namespace globals
{
	// settings for a 'flight' view camera system
	const float YAW{ -90.0f };
	const float PITCH{ 0.0f };
	const float SPEED{ 2.5f };
	const float SENSITIVITY{ 0.1f };
	const float ZOOM{ 45.0f };
}