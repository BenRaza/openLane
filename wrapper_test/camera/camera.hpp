#pragma once

#include "../player/player.hpp"
#include "p6/p6.h"

class Camera {
private:
    glm::vec3 _position{};
    Player*   _target;
    float     _distance{};
    float     _height{};
    float     _heightAngle{};
    float     _planarAngle = 0;
    float     _planarDistance{};
    float     _rotateSpeed = 0.02;
    void      rotate(float angle);
    void      setAngle(float angle);
    float     findHeight() const;
    bool      _isLocked = true;

public:
    glm::vec3 getPosition() { return _position; }
    void      init(Player* player, float distance, float height);
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