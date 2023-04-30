#pragma once

#include "../player/player.hpp"
#include "p6/p6.h"

class Camera {
private:
    glm::vec3   _position{};
    Player*     _target;
    float       _distance{};
    float       _height{};
    float       _heightAngle{};
    float       _planarAngle = 0;
    float       _planarDistance{};
    const float _rotateSpeed = 0.02;
    const float _minDistance = 1.f;
    const float _maxDistance = 5;
    void        rotate(float angle);
    void        setAngle(float angle);
    float       findHeight() const;
    bool        _isLocked = true;

public:
    glm::vec3 getPosition() { return _position; }
    float     getPlanarDistance() const { return _planarDistance; }
    void      init(Player* player, float distance, float height);
    void      moveAway();
    void      moveCloser();
    void      rotateLeft();
    void      rotateRight();
    void      rotateUp();
    void      rotateDown();
    void      update()
    {
        init(_target, _distance, _height);
    }

    void lockCamera();
};