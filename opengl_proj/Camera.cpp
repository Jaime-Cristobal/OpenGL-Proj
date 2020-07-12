#include "Camera.h"

using crt::Camera;


// constructor with vector
Camera::Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
	float yawP = globals::YAW, float pitchP = globals::PITCH)
	: frontVector(glm::vec3(0.0f, 0.0f, -1.0f)), 
	  movementSpeed(globals::SPEED), 
	  mouseSensitivity(globals::SENSITIVITY),
	  zoom(globals::ZOOM), 
	  position(pos), 
	  worldUp(up), 
	  yaw(yawP), 
	  pitch(pitchP)
{
	updateCameraVectors();
}

// constructor with scalar
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yawP, float pitchP)
	: frontVector(glm::vec3(0.0f, 0.0f, -1.0f)), 
	  movementSpeed(globals::SPEED), 
	  mouseSensitivity(globals::SENSITIVITY),
	  zoom(globals::ZOOM), 
	  position(glm::vec3(posX, posY, posZ)), 
	  worldUp(glm::vec3(upX, upY, upZ)), 
	  yaw(yawP), 
	  pitch(pitchP)
{
	updateCameraVectors();
}

void Camera::processKeyBoard(CameraMovement direction, float delta)
{
	float velocity = movementSpeed * delta;
	switch (direction)
	{
	case CameraMovement::FORWARD:
		position += frontVector * velocity;
		break;
	case CameraMovement::BACKWARD:
		position -= frontVector * velocity;
		break;
	case CameraMovement::LEFT:
		position -= rightVector * velocity;
		break;
	case CameraMovement::RIGHT:
		position += rightVector * velocity;
		break;
	}
}

void Camera::moveForward(float delta)
{
	float velocity = movementSpeed * delta;
	position += frontVector * velocity;
}

void Camera::moveBackward(float delta)
{
	float velocity = movementSpeed * delta;
	position -= frontVector * velocity;
}

void Camera::moveLeftward(float delta)
{
	float velocity = movementSpeed * delta;
	position -= rightVector * velocity;
}

void Camera::moveRightward(float delta)
{
	float velocity = movementSpeed * delta;
	position += rightVector * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		else if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// update front, right, and up vector using updated euler angles
	updateCameraVectors();
}

/*
* Processes input received from a mouse scroll-wheel event. Only requires
* input on the vertical wheel-axis.
*/
void Camera::processMouseScroll(float yOffset)
{
	zoom -= static_cast<float>(yOffset);
	if (zoom < 1.0f)
		zoom = 1.0f;
	else if (zoom > 45.0f)
		zoom = 45.0f;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + frontVector, upVector);
}

void Camera::updateCameraVectors()
{
	// calculate new front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontVector = glm::normalize(front);

	// also re-calculate the right and up vector
	// NOTE: Normalize the vectors, because their length gets closer to 0
	//		 the more you look up or down which results in slow movement.
	rightVector = glm::normalize(glm::cross(frontVector, worldUp));
	upVector = glm::normalize(glm::cross(rightVector, frontVector));
}