#include "Camera.h"
#include <assert.h>

Camera::~Camera()
{
}

void Camera::SetPosition(glm::vec4 position)
{
	m_worldTransform[3] = position;
}

glm::vec4 Camera::getPosition() const
{
	return m_worldTransform[3];
}

void Camera::translate(glm::vec4 positionModifier)
{
	m_worldTransform[3] += positionModifier;
}


const glm::mat4 & Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

void Camera::SetProjectionMatrix(glm::mat4 value)
{
	assert(m_hasSetProjectionMatrix);
	m_projectionMatrix = value;

}

void Camera::SetHasSetProjectionMatrix(bool value)
{
	m_hasSetProjectionMatrix = value;
}
