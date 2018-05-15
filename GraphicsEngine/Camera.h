#pragma once
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>

#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning ( pop )

class Camera
{
public:

	virtual ~Camera();

	void SetPosition(glm::vec4 position);
	glm::vec4 getPosition() const;

	void translate(glm::vec4 positionModifier);

	const glm::mat4& getTransform() const { return m_worldTransform; }
	glm::mat4& getTransform() { return m_worldTransform; }

	glm::mat4 getViewMatrix() const { return glm::inverse(m_worldTransform); }

	const glm::mat4& GetProjectionMatrix() const;

	void SetProjectionMatrix(glm::mat4 value);

	virtual void update(struct GLFWwindow* window, float deltaTime) {}

	void SetHasSetProjectionMatrix(bool value);

private:
	glm::mat4 m_worldTransform = glm::mat4(1);
	glm::mat4 m_projectionMatrix = glm::mat4(1);
	bool m_hasSetProjectionMatrix = false;
};

