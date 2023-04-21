#include "camera.hpp"
#include <cmath>

void Camera::init(glm::vec3 object, float distance, float height)
{
    _distance = distance;
    if (height >= _distance - _rotateSpeed)
    {
        _height = _distance - _rotateSpeed;
    }
    else
    {
        _height = height;
    }
    _heightAngle    = std::asin(height / distance);
    _planarDistance = height / std::tan(_heightAngle);
    _position       = {object.x - (_planarDistance * std::cos(_planarAngle)), object.y + _height, object.z - (_planarDistance * std::sin(_planarAngle))};
    _target         = object;
}

void Camera::setAngle(float angle)
{
    _planarAngle = std::fmod(angle, (2 * p6::PI));
}

void Camera::rotate(float angle)
{
    setAngle(_planarAngle + angle);
    std::cout << _planarAngle << std::endl;
    _position = {_target.x - (_planarDistance * std::cos(_planarAngle)), _target.y + _height, _target.z - (_planarDistance * std::sin(_planarAngle))};
}

void Camera::rotateLeft()
{
    rotate(_rotateSpeed);
}

void Camera::rotateRight()
{
    rotate(-_rotateSpeed);
}

void Camera::rotateUp()
{
    _heightAngle += _rotateSpeed;
    _height = findHeight();
    init(_target, _distance, _height);
}

void Camera::rotateDown()
{
    _heightAngle -= _rotateSpeed;
    _height = findHeight();
    init(_target, _distance, _height);
}

float Camera::findHeight()
{
    return std::sin(_heightAngle) * _distance;
}