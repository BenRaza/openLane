#include <cmath>
#include <cstdlib>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <random>
#include <vector>
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "boids.hpp"

std::random_device rd;
std::mt19937       mt(rd());

int main(int argc, char* argv[])
{
    std::string                            text = "Hello";
    auto                                   ctx  = p6::Context{{.title = "Simple-p6-Setup"}};
    std::uniform_real_distribution<double> randAngle(0, 2 * PI);
    std::uniform_real_distribution<double> randHeight(-1, 1);
    std::uniform_real_distribution<double> randWidth(-ctx.aspect_ratio(), ctx.aspect_ratio());
    float                                  screenRatio      = ctx.aspect_ratio();
    float                                  RATIO_SEPARATION = 5;
    float                                  RATIO_ALIGNEMENT = 10;
    float                                  RATIO_COHESION   = 1;
    float                                  RAY_OF_FORCE     = 0.25;
    unsigned int                           NUMBER_OF_BOIDS  = 50;
    float                                  speed            = 0.007;
    { // Run the tests
        if (doctest::Context{}.run() != 0)
        {
            return EXIT_FAILURE;
        }
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
        {
            return EXIT_SUCCESS;
        }
    }

    // Actual app
    // auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    std::vector<Boids> boids;

    for (size_t i = 0; i < NUMBER_OF_BOIDS; i++)
    {
        glm::vec3 nexVec(randWidth(mt), 5, randHeight(mt));
        boids.emplace_back(nexVec, speed);
        float angle = randAngle(mt);
        boids[i].setAngle(angle);
        // boids[i].setDirection(glm::vec2(speed * glm::cos(angle), speed * glm::sin(angle)));
    }

    ctx.imgui = [&]() {
        ImGui::Begin("Test3");
        ImGui::SliderFloat("Ratio Separation", &RATIO_SEPARATION, 0.f, 50.f);
        ImGui::SliderFloat("Ratio Alignement", &RATIO_ALIGNEMENT, 0.f, 50.f);
        ImGui::SliderFloat("Ratio Cohesion", &RATIO_COHESION, 0.f, 50.f);
        ImGui::SliderFloat("Distance of force", &RAY_OF_FORCE, 0.f, 1.f);
        ImGui::End();
    };

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::PurpleHeart);
        // ctx.circle(
        //     p6::Center{ctx.mouse()},
        //     p6::Radius{0.2f}
        // );

        for (Boids& boid : boids)
        {
            ctx.equilateral_triangle(
                p6::Center{boid.getPosition()},
                p6::Radius{0.05f},
                p6::Rotation{p6::Radians(boid.getAngle())}
            );
            glm::vec3 separationForce = boid.calculateSeparationForce(boids, RAY_OF_FORCE);
            glm::vec3 aligmentForce   = boid.calculateAlignmentForce(boids, RAY_OF_FORCE);
            glm::vec3 cohesionForce   = boid.calculateCohesionForce(boids, RAY_OF_FORCE);
            glm::vec3 steeringForce   = separationForce * RATIO_SEPARATION + aligmentForce * RATIO_ALIGNEMENT + cohesionForce * RATIO_COHESION;
            // // boid.setDirection(boid.getDirection() + acc);
            boid.useForce(steeringForce);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();

    return 0;
}