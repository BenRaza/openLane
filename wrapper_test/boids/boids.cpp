#include "boids.hpp"
#include <iterator>
#include <vector>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/geometric.hpp"

float PI         = glm::pi<float>();
float sizeOfCube = 5;

float getPlanarAngle(glm::vec3 direction)
{
    glm::vec2 angularDir(direction.x, direction.z);
    float     distance = glm::distance(angularDir, glm::vec2(0.f, 0.f));
    float     x        = (angularDir.x / distance);
    float     y        = (angularDir.y / distance);
    if (x > 0)
    {
        return std::asin(y);
    }
    return std::acos(y) + (p6::PI / 2);

    return std::asin(y);
}

Boids::Boids(float speed)
{
    std::random_device                     rd;
    std::mt19937                           mt(rd());
    std::uniform_real_distribution<double> randX(-sizeOfCube + 0.5, sizeOfCube - 0.5);
    std::uniform_real_distribution<double> randY(-sizeOfCube + 0.5, sizeOfCube - 0.5);

    _position = glm::vec3((randX(mt), 5, randY(mt)));
    _speed    = speed;
}

void makeBorder(float& position)
{
    if (position >= sizeOfCube)
    {
        position = sizeOfCube - 0.01;
    }
    else if (position <= sizeOfCube)
    {
        position = -sizeOfCube + 0.01;
    }
}

void invertPosition(float& position, float& direction)
{
    if (position + direction > sizeOfCube || position + direction < -sizeOfCube)
    {
        direction *= -1;
    }
}

void Boids::setPosition(glm::vec3 newPos)
{
    // _position = newPos;
    // if (_position.x > sizeOfCube)
    // {
    //     _position.x = sizeOfCube - 0.01;
    // }
    // else if (_position.x < -sizeOfCube)
    // {
    //     _position.x = -sizeOfCube + 0.01;
    // }
    // if (_position.y > sizeOfCube)
    // {
    //     _position.y = sizeOfCube - 0.01;
    // }
    // else if (_position.y < -sizeOfCube)
    // {
    //     _position.y = -sizeOfCube + 0.01;
    // }
    // if (_position.z > sizeOfCube)
    // {
    //     _position.z = sizeOfCube - 0.01;
    // }
    // else if (_position.z < sizeOfCube)
    // {
    //     _position.z = -sizeOfCube + 0.01;
    // }
    makeBorder(_position.x);
    makeBorder(_position.y);
    makeBorder(_position.z);
}

void Boids::setDirection(glm::vec3 newDir)
{
    _angle     = glm::atan<float>(newDir.x, newDir.y);
    _direction = _speed * glm::normalize(newDir);
}

void Boids::useForce(glm::vec3 extForce)
{
    const glm::vec3 newForce = extForce * .0004f;
    setDirection(getDirection() + newForce);
    // if (getPosition().x + getDirection().x > screen || getPosition().x + getDirection().x < -screen)
    // {
    //     m_direction.x *= -1;
    // }
    // if (getPosition().y + getDirection().y > 1.f || getPosition().y + getDirection().y < -1.f)
    // {
    //     m_direction.y *= -1;
    // }
    invertPosition(_position.x, _direction.x);
    invertPosition(_position.y, _direction.y);
    invertPosition(_position.z, _direction.z);
    // setPosition(_position + _direction);
    // std::cout << _position.x << std::endl;
    _position += _direction;
}

void Boids::init()
{
    std::random_device                     rd;
    std::mt19937                           mt(rd());
    std::uniform_real_distribution<double> randAngle(0, 2 * PI);
    float                                  angle = randAngle(mt);
    setAngle(angle);
}

void Boids::update(const std::vector<Boids>& boids, float range, float separation, float alignment, float cohesion, const p6::Shader& shader)
{
    glm::vec3 separationForce = calculateSeparationForce(boids, range);
    glm::vec3 aligmentForce   = calculateAlignmentForce(boids, range);
    glm::vec3 cohesionForce   = calculateCohesionForce(boids, range);
    glm::vec3 steeringForce   = separationForce * separation + aligmentForce * alignment + cohesionForce * cohesion;
    // boid.setDirection(boid.getDirection() + acc);
    useForce(steeringForce);
    _planarAngle = getPlanarAngle(_direction);

    glm::mat4 base = glm::mat4(1.0);

    base = glm::translate(base, glm::vec3(_position.x, _position.y, _position.z));
    base = glm::rotate(base, p6::PI, glm::vec3(1.0f, 0.0f, 0.0f));
    base = glm::rotate(base, -p6::PI / 2.f, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::rotate(base, _planarAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::scale(base, glm::vec3(0.03));

    shader.set("model", base);
    ufo.Draw(shader.id());
}

glm::vec3 Boids::calculateSeparationForce(std::vector<Boids> boids, float ray)
{
    glm::vec3 totalForce(0.f, 0.f, 0.f);
    for (Boids& boid : boids)
    {
        float test = glm::distance(getPosition(), getPosition());
        if (test < ray && test > .001f)
        {
            totalForce.x += ((getPosition().x - boid.getPosition().x) / glm::distance(getPosition(), boid.getPosition()));
            totalForce.y += ((getPosition().y - boid.getPosition().y) / glm::distance(getPosition(), boid.getPosition()));
            totalForce.z += ((getPosition().z - boid.getPosition().z) / glm::distance(getPosition(), boid.getPosition()));
        }
    }
    return totalForce;
}

glm::vec3 Boids::calculateAlignmentForce(std::vector<Boids> boids, float ray)
{
    glm::vec3 averageDirection(0.f, 0.f, 0.f);
    for (Boids& boid : boids)
    {
        float test = glm::distance(getPosition(), boid.getPosition());
        if (test < ray && test > .001f)
        {
            averageDirection += boid.getDirection();
        }
    }
    averageDirection /= boids.size();
    if (averageDirection == glm::vec3(0.f, 0.f, 0.f))
    {
        return averageDirection;
    }
    return glm::normalize(averageDirection);
}

glm::vec3 Boids::calculateCohesionForce(std::vector<Boids> boids, float ray)
{
    glm::vec3 averagePosition(0.f, 0.f, 0.f);
    for (Boids& boid : boids)
    {
        float test = glm::distance(getPosition(), boid.getPosition());
        if (test < ray && test > .001f)
        {
            averagePosition += boid._position;
        }
    }
    averagePosition /= boids.size();
    return averagePosition;
}
