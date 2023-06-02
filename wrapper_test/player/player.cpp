#include "player.hpp"
#include <cmath>
#include "glm/ext/matrix_transform.hpp"

void movePositive(float& speed, const float& acceleration, const float& maxSpeed)
{
    if (speed + acceleration < maxSpeed)
    {
        speed += acceleration;
    }
    else
    {
        speed = maxSpeed;
    }
}

void moveNegative(float& speed, const float& acceleration, const float& minSpeed)
{
    if (speed - acceleration > -minSpeed)
    {
        speed -= acceleration;
    }
    else
    {
        speed = -minSpeed;
    }
}

void applySlow(float& speed, const float& acceleration, float factor)
{
    speed -= speed / factor;
    if (std::fabs(speed) <= acceleration / 10)
    {
        speed = 0;
    }
}

void Player::moveForward()
{
    movePositive(_speed, _acceleration, _maxSpeed);
    rotateLeftRingForward();
    rotateRightRingForward();
}

void Player::moveBackward()
{
    moveNegative(_speed, _acceleration, (_maxSpeed / 2));
    rotateLeftRingBackward();
    rotateRightRingBackward();
}

void Player::moveUp()
{
    movePositive(_verticalSpeed, _verticalAcceleration, _verticalMaxSpeed);
}

void Player::moveDown()
{
    moveNegative(_verticalSpeed, _verticalAcceleration, _verticalMaxSpeed);
}

void Player::rotateLeft()
{
    movePositive(_rotateSpeed, _rotateAcceleration, _rotateMaxSpeed);
    rotateLeftRingForward();
    rotateRightRingBackward();
}

void Player::rotateRight()
{
    moveNegative(_rotateSpeed, _rotateAcceleration, _rotateMaxSpeed);
    rotateLeftRingBackward();
    rotateRightRingForward();
}

void Player::rotateLeftRingForward()
{
    movePositive(_leftRingRotate, _rotateRingsAcceleration, _maxRotateRings);
}

void Player::rotateLeftRingBackward()
{
    moveNegative(_leftRingRotate, _rotateRingsAcceleration, _maxRotateRings / 1.5);
}

void Player::rotateRightRingForward()
{
    movePositive(_rightRingRotate, _rotateRingsAcceleration, _maxRotateRings);
}

void Player::rotateRightRingBackward()
{
    moveNegative(_rightRingRotate, _rotateRingsAcceleration, _maxRotateRings / 1.5);
}

void Player::update(const p6::Shader& shader)
{
    _planarRotation += _rotateSpeed;
    _direction = glm::vec3(std::cos(_planarRotation), _spawnedDirection.y, std::sin(_planarRotation));
    _position.x += _speed * _direction.x;
    _position.y += _verticalSpeed;
    _position.z -= _speed * _direction.z;
    _helicesRotate += fmod(0.5, 2 * p6::PI);
    applySlow(_rotateSpeed, _rotateAcceleration, 20);
    applySlow(_speed, _acceleration, 20);
    applySlow(_verticalSpeed, _verticalAcceleration, 20);
    applySlow(_rightRingRotate, _rotateRingsAcceleration, 10);
    applySlow(_leftRingRotate, _rotateRingsAcceleration, 10);

    glm::mat4 base = glm::mat4(1.0);

    base = glm::translate(base, glm::vec3(_position.x, _position.y, _position.z));
    base = glm::rotate(base, _planarRotation, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::rotate(base, -20.f * _speed, glm::vec3(0.0f, 0.f, 1.0f));
    base = glm::rotate(base, 10.f * _verticalSpeed, glm::vec3(0.0f, 0.f, 1.0f));
    base = glm::rotate(base, -3.f * _rotateSpeed, glm::vec3(1.0f, 0.f, 0.f));
    base = glm::rotate(base, p6::PI, glm::vec3(1.0f, 0.0f, 0.0f));
    base = glm::rotate(base, -p6::PI / 2.f, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::scale(base, glm::vec3(0.03));

    shader.set("model", base);
    flyingDrone.Draw(shader.id());

    base = glm::translate(base, glm::vec3(5.73, -0.9, 0.27));
    base = glm::rotate(base, -20.f * _speed, glm::vec3(1.0f, 0.f, 0.0f));
    base = glm::rotate(base, 2 * _rightRingRotate, glm::vec3(1.0f, 0.f, 0.0f));

    shader.set("model", base);
    circleLeft.Draw(shader.id());

    base = glm::rotate(base, _helicesRotate, glm::vec3(0.f, 1.f, 0.f));

    shader.set("model", base);
    helicesLeft.Draw(shader.id());

    base = glm::rotate(base, -_helicesRotate, glm::vec3(0.f, 1.f, 0.f));
    base = glm::rotate(base, -2 * _rightRingRotate, glm::vec3(1.0f, 0.f, 0.0f));
    base = glm::translate(base, glm::vec3(-11.46, 0.0, 0.0));
    base = glm::rotate(base, 2 * _leftRingRotate, glm::vec3(1.0f, 0.f, 0.0f));

    shader.set("model", base);
    circleRight.Draw(shader.id());

    base = glm::rotate(base, _helicesRotate, glm::vec3(0.f, 1.f, 0.f));

    shader.set("model", base);
    helicesRight.Draw(shader.id());

    base = glm::mat4(1.0);
    shader.set("model", base);
    // shader.set("model", base);
}
