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

    _position.x = randX(mt);
    _position.y = randX(mt);
    _position.z = randY(mt);

    _speed = speed;
}

void invertPosition(float& position, float& direction)
{
    if (position + direction > sizeOfCube)
    {
        position -= 1.8f * sizeOfCube;
    }
    else if (position + direction < -sizeOfCube)
    {
        position += 1.8f * sizeOfCube;
    }
}

void Boids::setDirection(glm::vec3 newDir)
{
    _angle = glm::atan<float>(newDir.x, newDir.z);
    _direction += glm::vec3(newDir.x, 0, newDir.z);
    if (_direction != glm::vec3(0.f, 0.f, 0.f))
    {
        _direction = glm::normalize(_direction);
    }
}

void Boids::useForce(glm::vec3 extForce)
{
    const glm::vec3 newForce = extForce;
    setDirection(newForce);
    invertPosition(_position.x, _direction.x);
    invertPosition(_position.y, _direction.y);
    invertPosition(_position.z, _direction.z);
    _position += _speed * _direction;
}

void Boids::init()
{
    std::random_device                     rd;
    std::mt19937                           mt(rd());
    std::uniform_real_distribution<double> randAngle(0, 2 * PI);
    float                                  angle = randAngle(mt);
    setAngle(angle);
}

void Boids::update(std::vector<Boids>& boids, float range, float separation, float alignment, float cohesion, const p6::Shader& shader)
{
    glm::vec3 separationForce = calculateSeparationForce(boids, range);
    glm::vec3 aligmentForce   = calculateAlignmentForce(boids, range);
    glm::vec3 cohesionForce   = calculateCohesionForce(boids, range);
    glm::vec3 steeringForce   = separationForce * separation + aligmentForce * alignment + cohesionForce * cohesion;
    useForce(steeringForce);
    _planarAngle = getPlanarAngle(_direction);
    rotateBase();

    glm::mat4 base = glm::mat4(1.0);

    base = glm::translate(base, glm::vec3(_position.x, _position.y, _position.z));
    base = glm::rotate(base, p6::PI, glm::vec3(1.0f, 0.0f, 0.0f));
    base = glm::rotate(base, -p6::PI / 2.f, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::rotate(base, _planarAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::scale(base, glm::vec3(0.03));
    base = glm::rotate(base, 0.4f, glm::vec3(1.0f, 0.0f, 0.0f));

    shader.set("model", base);
    top.Draw(shader.id());
    bot.Draw(shader.id());

    base = glm::rotate(base, _rotationBase, glm::vec3(0.0f, 1.0f, 0.0f));

    shader.set("model", base);
    ufo.Draw(shader.id());
}

glm::vec3 Boids::calculateSeparationForce(std::vector<Boids>& boids, float ray)
{
    glm::vec3 totalForce(0.f, 0.f, 0.f);
    for (Boids& boid : boids)
    {
        float test = glm::distance(getPosition(), boid.getPosition());
        if (test < ray && test > .00001f)
        {
            totalForce.x += ((getPosition().x - boid.getPosition().x) / glm::distance(getPosition(), boid.getPosition()));
            totalForce.y += ((getPosition().y - boid.getPosition().y) / glm::distance(getPosition(), boid.getPosition()));
            totalForce.z += ((getPosition().z - boid.getPosition().z) / glm::distance(getPosition(), boid.getPosition()));
        }
    }
    if (totalForce == glm::vec3(0.f, 0.f, 0.f))
    {
        return totalForce;
    }
    return glm::normalize(totalForce);
}

glm::vec3 Boids::calculateAlignmentForce(std::vector<Boids>& boids, float ray)
{
    glm::vec3 averageDirection(0.f, 0.f, 0.f);
    for (Boids& boid : boids)
    {
        float test = glm::distance(getPosition(), boid.getPosition());
        if (test < ray && test > .00001f)
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

glm::vec3 Boids::calculateCohesionForce(std::vector<Boids>& boids, float ray)
{
    glm::vec3 averagePosition(0.f, 0.f, 0.f);
    for (Boids& boid : boids)
    {
        float test = glm::distance(getPosition(), boid.getPosition());
        if (test < ray && test > .00001f)
        {
            averagePosition += boid._position;
        }
    }
    averagePosition /= boids.size();
    if (averagePosition == glm::vec3(0.f, 0.f, 0.f))
    {
        return averagePosition;
    }
    return glm::normalize(averagePosition);
}
