#include"Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	mouseSensitivity = SENSITIVITY;
	zoom = ZOOM;
	updateCameraVectors();

}
glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(position, position + front, up);
}
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;

}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

void Camera::updateCameraVectors() {
	glm::vec3 l_Front;

	l_Front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
	l_Front.y = sin(glm::radians(pitch));
	l_Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(l_Front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}