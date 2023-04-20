#include "camera.hpp"
#include <cmath>

void Camera::init(glm::vec3 object, float distance, float height)
{
    m_distance = distance;
    if (height >= m_distance - m_rotateSpeed)
    {
        m_height = m_distance - m_rotateSpeed;
    }
    else
    {
        m_height = height;
    }
    m_heightAngle    = std::asin(height / distance);
    m_planarDistance = height / std::tan(m_heightAngle);
    m_position       = {object.x - (m_planarDistance * std::cos(m_planarAngle)), object.y + m_height, object.z - (m_planarDistance * std::sin(m_planarAngle))};
    m_target         = object;
}

void Camera::setAngle(float angle)
{
    m_planarAngle = std::fmod(angle, (2 * p6::PI));
}

void Camera::rotate(float angle)
{
    setAngle(m_planarAngle + angle);
    std::cout << m_planarAngle << std::endl;
    m_position = {m_target.x - (m_planarDistance * std::cos(m_planarAngle)), m_target.y + m_height, m_target.z - (m_planarDistance * std::sin(m_planarAngle))};
}

void Camera::rotateLeft()
{
    rotate(m_rotateSpeed);
}

void Camera::rotateRight()
{
    rotate(-m_rotateSpeed);
}

void Camera::rotateUp()
{
    m_heightAngle += m_rotateSpeed;
    m_height = findHeight();
    init(m_target, m_distance, m_height);
}

void Camera::rotateDown()
{
    m_heightAngle -= m_rotateSpeed;
    m_height = findHeight();
    init(m_target, m_distance, m_height);
}

float Camera::findHeight()
{
    return std::sin(m_heightAngle) * m_distance;
}