#include "camera.hpp"
#include <cmath>

float getAngle(Camera camera, Player player)
{
    float x = (camera.getPosition().x - player.getPosition().x) / camera.getPlanarDistance();
    float z = (camera.getPosition().z - player.getPosition().z) / camera.getPlanarDistance();
    if (x < 0)
    {
        return std::asin(z);
    }
    return std::acos(z) + (p6::PI / 2);

    return std::asin(z);
}

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
        _position    = {player->getPosition().x - (_planarDistance * player->getDirection().x), player->getPosition().y + _height, player->getPosition().z + (_planarDistance * player->getDirection().z)};
        _planarAngle = getAngle(*this, *player);
    }
    else
    {
        _position = {player->getPosition().x - (_planarDistance * std::cos(_planarAngle)), player->getPosition().y + _height, player->getPosition().z + (_planarDistance * std::sin(_planarAngle))};
    }
    _target = player;
}

void Camera::setAngle(float angle)
{
    _planarAngle = std::fmod(angle, (2 * p6::PI));
}

void Camera::moveAway()
{
    if (_distance + 0.05f < _maxDistance)
    {
        _distance += 0.05f;
    }
}

void Camera::moveCloser()
{
    if (_distance - 0.05f > _minDistance)
    {
        _distance -= 0.05f;
    }
}

void Camera::rotate(float angle)
{
    _isLocked = false;
    setAngle(_planarAngle + angle);
    //_position = {_target->getPosition().x - (_planarDistance * std::cos(_planarAngle)), _target->getPosition().y + _height, _target->getPosition().z - (_planarDistance * std::sin(_planarAngle))};
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
    _heightAngle += _rotateSpeed;
    _height = findHeight();
}

void Camera::rotateDown()
{
    _heightAngle -= _rotateSpeed;
    _height = findHeight();
}

float Camera::findHeight() const
{
    return std::sin(_heightAngle) * _distance;
}

void Camera::lockCamera()
{
    _isLocked = true;
}
