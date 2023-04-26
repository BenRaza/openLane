#include "camera.hpp"
#include <cmath>

void Camera::init(Player* player, float distance, float height)
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
    if (_isLocked)
    {
        _position = {player->getPosition().x - (_planarDistance * player->getDirection().x), player->getPosition().y + _height, player->getPosition().z + (_planarDistance * player->getDirection().z)};
    }
    //_position = {player->getPosition().x - (_planarDistance * std::sin(_planarAngle)), player->getPosition().y + _height, player->getPosition().z - (_planarDistance * std::cos(_planarAngle))};
    _target = player;
}

void Camera::setAngle(float angle)
{
    _planarAngle = std::fmod(angle, (2 * p6::PI));
}

void Camera::rotate(float angle)
{
    _isLocked = false;
    setAngle(_planarAngle + angle);
    _position = {_target->getPosition().x - (_planarDistance * std::sin(_planarAngle)), _target->getPosition().y + _height, _target->getPosition().z - (_planarDistance * std::cos(_planarAngle))};
}

void Camera::rotateLeft()
{
    rotate(-_rotateSpeed);
}

void Camera::rotateRight()
{
    rotate(+_rotateSpeed);
}

void Camera::rotateUp()
{
    _isLocked = false;
    _heightAngle += _rotateSpeed;
    _height = findHeight();
}

void Camera::rotateDown()
{
    _isLocked = false;
    _heightAngle -= _rotateSpeed;
    _height = findHeight();
}

float Camera::findHeight() const
{
    return std::sin(_heightAngle) * _distance;
}