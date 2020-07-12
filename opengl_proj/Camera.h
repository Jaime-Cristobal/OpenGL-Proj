#pragma once

#include "CameraPOD.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


namespace crt 
{
	class Camera
	{
	private:
		// camera attributes
		glm::vec3 position;
		glm::vec3 frontVector;
		glm::vec3 upVector;
		glm::vec3 rightVector;
		glm::vec3 worldUp;
		// euler angles
		float yaw;
		float pitch;
		// camera options
		float movementSpeed;
		float mouseSensitivity;
		float zoom;

		void updateCameraVectors();

	public:
		// constructor with vector
		Camera(glm::vec3 pos, glm::vec3 up, float yawP, float pitchP);
		// constructor with scalar
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		void processKeyBoard(CameraMovement direction, float delta);
		void moveForward(float delta);
		void moveBackward(float delta);
		void moveLeftward(float delta);
		void moveRightward(float delta);
		void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch);
		void processMouseScroll(float yOffset);
		glm::mat4 getViewMatrix() const;
	};
}