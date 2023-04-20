#include "camera.hpp"
#include <cmath>

void Camera::init(glm::vec3 object, float distance, float height)
{
    m_distance = distance;
    if (height > distance)
    {
        m_height = distance;
    }
    else
    {
        m_height = height;
    }
    float heightAngle = std::asin(height / distance);
    std::cout << heightAngle << std::endl;
    m_planarDistance = height * std::cos(heightAngle);
    m_position       = {object.x - m_planarDistance * std::cos(m_planarAngle), object.y + m_height, object.z * std::sin(m_planarAngle)};
    m_target         = object;
}

void Camera::setAngle(float angle)
{
    m_planarAngle = std::fmod(angle, (2 * p6::PI));
}

void Camera::rotate(float angle)
{
    setAngle(m_planarAngle + angle);
    m_position = {m_target.x - m_planarDistance * std::cos(m_planarAngle), m_target.y, m_target.z * std::sin(m_planarAngle)};
}

void Camera::rotateLeft()
{
    rotate(-m_rotateSpeed);
}

void Camera::rotateRight()
{
    rotate(m_rotateSpeed);
}
