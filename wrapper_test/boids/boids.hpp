#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include "../loaderGLTF/Model.h"
#include "glm/ext/scalar_constants.hpp"
#include "p6/p6.h"

extern float PI;

class Boids {
private:
    glm::vec3 _position{};
    glm::vec3 _direction{};
    glm::vec2 _angularDirection{};
    float     _planarAngle{};
    float     _speed{};
    float     _angle{};

    Model ufo = Model("./assets/drone.gltf");

public:
    Boids(float speed);

    glm::vec3 getPosition()
    {
        return _position;
    }
    void setPosition(glm::vec3 newPos);

    glm::vec3 getDirection()
    {
        return _direction;
    }
    void  setDirection(glm::vec3 newDir);
    float getAngle() const
    {
        return _angle;
    }
    void setAngle(float newAngle)
    {
        _angle            = std::fmod(newAngle, (2.f * PI));
        _angularDirection = glm::vec2(_speed * std::cos(_angle), _speed * std::sin(_angle));
        _direction        = glm::vec3(_speed * std::cos(_angle), 0, _speed * std::sin(_angle));
    }
    void  useForce(glm::vec3 extForce);
    float getSpeed() const
    {
        return _speed;
    }
    void setSpeed(float newSpeed)
    {
        _speed = newSpeed;
    }
    // glm::vec2 getAcceleration()
    // {
    //     return acceleration;
    // }
    void      init();
    void      update(const std::vector<Boids>& boids, float range, float separation, float alignment, float cohesion, const p6::Shader& shader);
    glm::vec3 calculateSeparationForce(std::vector<Boids> boids, float ray);
    glm::vec3 calculateAlignmentForce(std::vector<Boids> boids, float ray);
    glm::vec3 calculateCohesionForce(std::vector<Boids> boids, float ray);
};