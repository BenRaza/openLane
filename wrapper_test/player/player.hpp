#pragma once
#include "../loaderGLTF/Model.h"
#include "p6/p6.h"

class Player {
private:
    const float _acceleration = 0.001;
    const float _maxSpeed     = 0.1;

    const float _rotateAcceleration = 0.00390625;
    const float _rotateMaxSpeed     = 0.0625;

    const float _verticalAcceleration = 0.001;
    const float _verticalMaxSpeed     = 0.1;

    const float _rotateRingsAcceleration = 0.03;
    const float _maxRotateRings          = 0.5;

    Model flyingDrone  = Model("./assets/drone.gltf");
    Model circleLeft   = Model("./assets/circle.gltf");
    Model helicesLeft  = Model("./assets/helices.gltf");
    Model circleRight  = Model("./assets/circle.gltf");
    Model helicesRight = Model("./assets/helices.gltf");

    glm::vec3 _position{};
    glm::vec3 _spawnedDirection{};
    glm::vec3 _direction{};
    float     _speed           = 0;
    float     _verticalSpeed   = 0;
    float     _rotateSpeed     = 0;
    float     _planarRotation  = 0;
    float     _helicesRotate   = 0;
    float     _leftRingRotate  = 0;
    float     _rightRingRotate = 0;

    void rotateLeftRingForward();
    void rotateLeftRingBackward();
    void rotateRightRingForward();
    void rotateRightRingBackward();

public:
    explicit Player(glm::vec3 position = glm::vec3{0}, glm::vec3 direction = glm::vec3(1.f, 0.f, 0.f))
        : _position(position), _spawnedDirection(direction), _direction(direction){};
    glm::vec3 getPosition() { return _position; };
    glm::vec3 getDirection() { return _direction; };
    void      moveForward();
    void      moveBackward();
    void      moveUp();
    void      moveDown();
    void      rotateLeft();
    void      rotateRight();
    void      update(const p6::Shader& shader);
};