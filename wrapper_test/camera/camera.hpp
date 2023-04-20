#pragma once

#include "p6/p6.h"

class Camera {
private:
    glm::vec3 m_position{};
    glm::vec3 m_target;
    float     m_distance{};
    float     m_height{};
    float     m_heightAngle{};
    float     m_planarAngle = 0;
    float     m_planarDistance{};
    float     m_rotateSpeed = 0.02;
    void      rotate(float angle);
    void      setAngle(float angle);
    float     findHeight();

public:
    glm::vec3 getPosition() { return m_position; }
    glm::vec3 getTarget() { return m_target; }
    void      init(glm::vec3 object, float distance, float height);
    void      rotateLeft();
    void      rotateRight();
    void      rotateUp();
    void      rotateDown();
};