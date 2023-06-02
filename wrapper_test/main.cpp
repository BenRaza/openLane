#include <cmath>
#include <vector>
#include "camera/camera.hpp"
#include "controls/controls.hpp"
#include "glimac/default_shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "player/player.hpp"
// #include "src-common/glimac/sphere_vertices.hpp"
#include "./loaderGLTF/Model.h"
#include "boids/boids.hpp"
#include "vertex3D/vertex3D.hpp"
#include "wrapper/wrapper.hpp"

int main()
{
    glm::mat4 projection = glm::perspective(glm::radians(45.f), static_cast<float>(1280) / static_cast<float>(720), 0.001f, 100.0f);

    float cameraDistance   = 2;
    float cameraBaseHeight = 1;

    float        RATIO_SEPARATION  = 0.04;
    float        RATIO_ALIGNEMENT  = 0.05;
    float        RATIO_COHESION    = 0.03;
    float        RAY_OF_FORCE      = 2;
    unsigned int NUMBER_OF_BOIDS   = 30;
    float        speed             = 0.015;
    float        LIGHT_ANGLE       = 12.5;
    float        LIGHT_OUTER_ANGLE = 17.5;
    float        RED               = 127;
    float        BLUE              = 127;
    float        GREEN             = 127;

    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    Model skybox = Model("./assets/skyBox.gltf");
    Model dyson  = Model("./assets/dyson.gltf");

    glEnable(GL_DEPTH_TEST);

    const p6::Shader shader = p6::load_shader(
        "shaders/color2D.vs.glsl",
        "shaders/color2D.fs.glsl"
    );

    const p6::Shader shaderGLTF = p6::load_shader(
        "shaders/gltf.vs.glsl",
        "shaders/gltf.fs.glsl"
    );

    const p6::Shader shaderBox = p6::load_shader(
        "shaders/gltf2.vs.glsl",
        "shaders/gltf2.fs.glsl"
    );

    Player             drone{};
    std::vector<Boids> ufos{};

    for (unsigned int i = 0; i < NUMBER_OF_BOIDS; i++)
    {
        Boids boid(speed);
        boid.init();
        ufos.push_back(boid);
    }

    Camera camera{};
    // glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f);
    camera.init(&drone, cameraDistance, cameraBaseHeight);

    shaderGLTF.use();
    shaderGLTF.set("lightColor", glm::vec3(0.99, 0.94, 0.72));
    shaderGLTF.set("lightColor2", glm::vec3(0.8, 0.33, 0.0));
    shaderGLTF.set("lightPosition", glm::vec3(-75.0, 75, -75.0));
    shaderGLTF.set("lightPosition2", glm::vec3(150.0, 75, 150.0));

    shaderBox.use();
    glm::mat4 base = glm::mat4(1.0);
    base           = glm::scale(base, glm::vec3(50));
    shaderBox.set("model", base);

    ctx.imgui = [&]() {
        ImGui::Begin("Test3");
        ImGui::SliderFloat("Ratio Separation", &RATIO_SEPARATION, 0.001f, 1.f);
        ImGui::SliderFloat("Ratio Alignement", &RATIO_ALIGNEMENT, 0.001f, 1.f);
        ImGui::SliderFloat("Ratio Cohesion", &RATIO_COHESION, 0.001f, 1.f);
        ImGui::SliderFloat("Distance of force", &RAY_OF_FORCE, 0.1f, 10.f);
        ImGui::SliderFloat("Angle of Light", &LIGHT_ANGLE, 0.f, 30.f);
        ImGui::SliderFloat("Smoothness", &LIGHT_OUTER_ANGLE, 0.f, 50.f);
        ImGui::SliderFloat("Light RED", &RED, 0, 255);
        ImGui::SliderFloat("Light GREEN", &GREEN, 0, 255);
        ImGui::SliderFloat("Light BLUE", &BLUE, 0, 255);
        ImGui::End();
    };

    ctx.update = [&]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (LIGHT_ANGLE > LIGHT_OUTER_ANGLE)
        {
            LIGHT_OUTER_ANGLE = LIGHT_ANGLE;
        }
        glm::mat4 view = glm::lookAt(camera.getPosition(), drone.getPosition(), {0, 1, 0});
        shaderGLTF.use();
        shaderGLTF.set("projection", projection);
        shaderGLTF.set("view", view);
        shaderGLTF.set("camPos", camera.getPosition());
        glm::vec3 dir;
        dir.x = -drone.getDirection().x;
        dir.y = drone.getDirection().y + 0.4f;
        dir.z = drone.getDirection().z;
        shaderGLTF.set("spotLightPosition", drone.getPosition() - 0.15f * dir);
        shaderGLTF.set("spotLightDirection", dir);
        shaderGLTF.set("spotLightCutOff", glm::cos(glm::radians(LIGHT_ANGLE)));
        shaderGLTF.set("spotLightOuterCutOff", glm::cos(glm::radians(LIGHT_OUTER_ANGLE)));
        shaderGLTF.set("spotLightColor", glm::vec3(RED / 255.f, GREEN / 255.f, BLUE / 255.f));
        glm::mat4 base = glm::mat4(1.0);
        base           = glm::scale(base, glm::vec3(7));
        shaderGLTF.set("model", base);
        dyson.Draw(shaderGLTF.id());
        for (Boids& ufo : ufos)
        {
            ufo.update(ufos, RAY_OF_FORCE, RATIO_SEPARATION, RATIO_ALIGNEMENT, RATIO_COHESION, shaderGLTF);
        }
        drone.update(shaderGLTF);
        camera.update();

        shaderBox.use();
        shaderBox.set("projection", projection);
        shaderBox.set("view", view);
        skybox.Draw(shaderBox.id());

        checkInputs(ctx, camera, drone);
    };

    ctx.start();
    // form.finish();
}