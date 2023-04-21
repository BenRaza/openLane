#pragma once

#include "p6/p6.h"

class Camera {
private:
    glm::vec3 _position{};
    glm::vec3 _target;
    float     _distance{};
    float     _height{};
    float     _heightAngle{};
    float     _planarAngle = 0;
    float     _planarDistance{};
    float     _rotateSpeed = 0.02;
    void      rotate(float angle);
    void      setAngle(float angle);
    float     findHeight();

public:
    glm::vec3 getPosition() { return _position; }
    glm::vec3 getTarget() { return _target; }
    void      init(glm::vec3 object, float distance, float height);
    void      rotateLeft();
    void      rotateRight();
    void      rotateUp();
    void      rotateDown();
};