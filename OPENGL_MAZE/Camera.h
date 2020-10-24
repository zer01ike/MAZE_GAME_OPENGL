#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GL/glew.h"
#include "glm/gtx/string_cast.hpp"
#include "global.h"
#include <iostream>
#include <vector>
using namespace std;

const GLfloat YAW = 45.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.05f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3 front= glm::vec3(0.0f, 0.0f, -1.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM),lockpitch(true) {
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->Front = front;
		this->updateCameraVectors();
	}
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM), lockpitch(true)
	{
		this->Position = glm::vec3(posX, posY, posZ);
		this->WorldUp = glm::vec3(upX, upY, upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}
	glm::mat4 GetViewMatrix()
	{
		glm::mat4 view = glm::lookAt(this->Position, this->Position + this->Front, this->Up);
		//std::cout << glm::to_string(view) << std::endl;
		//std::cout << "p:" << glm::to_string(this->Position) << " f:" << glm::to_string(this->Front) << " yaw:" << this->Yaw << " pitch:" << this->Pitch << std::endl;
		return view;
	}

	~Camera() {};

	GLfloat Zoom;

	void ProcessKeyboard(Camera_Movement direction)
	{
		GLfloat velocity = this->MovementSpeed * 0.05;
		glm::vec3 temp_position;
		if (direction == FORWARD)
			temp_position = this->Position + this->Front * velocity;
		if (direction == BACKWARD)
			temp_position = this->Position - this->Front * velocity;
		if (direction == LEFT)
			temp_position = this->Position - this->Right * velocity;
		if (direction == RIGHT)
			temp_position = this->Position + this->Right * velocity;

		/*for (auto i : this->worldAABB) {
			if (temp_position.x < i.x_max && temp_position.x > i.x_min 
				&& temp_position.y < i.y_max && temp_position.y > i.y_min
				&& temp_position.z < i.z_max && temp_position.z > i.z_min) 
				return;
		}*/

		this->Position = temp_position;
	}

	glm::vec3 NextPostion(Camera_Movement direction) {
		GLfloat velocity = this->MovementSpeed * 0.05;
		glm::vec3 temp_position;
		if (direction == FORWARD)
			temp_position = this->Position + this->Front * velocity;
		if (direction == BACKWARD)
			temp_position = this->Position - this->Front * velocity;
		if (direction == LEFT)
			temp_position = this->Position - this->Right * velocity;
		if (direction == RIGHT)
			temp_position = this->Position + this->Right * velocity;
		return temp_position;
	}

	void UpdatePosition(glm::vec3 new_psition) {
		this->Position = new_psition;
	}

	/*void updateFront(GLfloat yaw, GLfloat pitch) {
		glm::vec3 front;
		front.x = cos(glm::radians(yaw))* cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		this->Front = glm::normalize(front);
	}*/

	void updateFront(float xoffset, float yoffset) {

		this->Yaw += xoffset * this->MouseSensitivity;
		this->Pitch -= yoffset * this->MouseSensitivity;
		if (this->lockpitch) {
			if (this->Pitch > 20.0f)
				this->Pitch = 20.0f;
			if (this->Pitch < -5.0f)
				this->Pitch = -5.0f;
			
		}
		this->updateCameraVectors();
		
	}


	glm::vec3 getPosition() {
		return Position;
	}

	void LockCameraPitch(bool lock) {
		this->lockpitch = lock;
	}
private:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	bool lockpitch;

	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->Up = glm::normalize(glm::cross(this->Right, this->Front));
	}

	
};

