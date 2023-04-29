#include "player.hpp"
#include <cmath>
#include "glm/ext/matrix_transform.hpp"

void Player::moveForward()
{
    if (_speed + _acceleration < _maxSpeed)
    {
        _speed += _acceleration;
    }
}

void Player::moveBackward()
{
    if (_speed - _acceleration > -(_maxSpeed / 2))
    {
        _speed -= _acceleration / 2;
    }
}

void Player::moveUp()
{
    if (_verticalSpeed + _verticalAcceleration < _verticalMaxSpeed)
    {
        _verticalSpeed += _verticalAcceleration;
    }
}

void Player::moveDown()
{
    if (_verticalSpeed - _verticalAcceleration > -_verticalMaxSpeed)
    {
        _verticalSpeed -= _verticalAcceleration;
    }
}

void Player::rotateLeft()
{
    if (_rotateSpeed + _rotateAcceleration < _rotateMaxSpeed)
    {
        _rotateSpeed += _rotateAcceleration;
    }
    else
    {
        _rotateSpeed = _rotateMaxSpeed;
    }
}

void Player::rotateRight()
{
    if (_rotateSpeed - _rotateAcceleration > -_rotateMaxSpeed)
    {
        _rotateSpeed -= _rotateAcceleration;
    }
    else
    {
        _rotateSpeed = -_rotateMaxSpeed;
    }
}

void Player::update(const p6::Shader& shader)
{
    _planarRotation += _rotateSpeed;
    _rotateSpeed -= _rotateSpeed / 20;
    if (std::fabs(_rotateSpeed) < _rotateAcceleration / 2)
    {
        _rotateSpeed = 0;
    }
    _direction = glm::vec3(std::cos(_planarRotation), _spawnedDirection.y, std::sin(_planarRotation));
    _position.x += _speed * _direction.x;
    _position.y += _verticalSpeed;
    _position.z -= _speed * _direction.z;
    _speed -= _speed / 20;
    _verticalSpeed -= _verticalSpeed / 20;
    if (std::fabs(_speed) < _rotateAcceleration / 10)
    {
        _speed = 0;
    }
    if (std::fabs(_verticalSpeed) < _verticalAcceleration / 10)
    {
        _verticalSpeed = 0;
    }

    glm::mat4 base = glm::mat4(1.0);

    base = glm::translate(base, glm::vec3(_position.x, _position.y, _position.z));
    base = glm::rotate(base, _planarRotation, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::rotate(base, -20.f * _speed, glm::vec3(0.0f, 0.f, 1.0f));
    base = glm::rotate(base, -3.f * _rotateSpeed, glm::vec3(1.0f, 0.f, 0.f));
    base = glm::rotate(base, p6::PI, glm::vec3(1.0f, 0.0f, 0.0f));
    base = glm::rotate(base, p6::PI, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::scale(base, glm::vec3(0.03));
    // base = glm::rotate(base, p6::PI / 2.f, glm::vec3(0.0f, 1.0f, 0.0f));

    shader.set("model", base);
}
