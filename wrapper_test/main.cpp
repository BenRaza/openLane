#include <cmath>
#include "camera/camera.hpp"
#include "controls/controls.hpp"
#include "glimac/default_shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "player/player.hpp"
// #include "src-common/glimac/sphere_vertices.hpp"
#include "./loaderGLTF/Model.h"
#include "vertex3D/vertex3D.hpp"
#include "wrapper/wrapper.hpp"

int main()
{
    glm::mat4 projection = glm::perspective(glm::radians(45.f), static_cast<float>(1280) / static_cast<float>(720), 0.001f, 100.0f);

    float cameraDistance   = 2;
    float cameraBaseHeight = 1;

    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    glEnable(GL_DEPTH_TEST);

    const p6::Shader shader = p6::load_shader(
        "shaders/color2D.vs.glsl",
        "shaders/color2D.fs.glsl"
    );

    const p6::Shader shaderGLTF = p6::load_shader(
        "shaders/gltf.vs.glsl",
        "shaders/gltf.fs.glsl"
    );

    // const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16);

    Wrapper form{};
    // for (vertice : vertices)
    Vertex3D ver1 = {glm::vec3(-0.5f, -0.5f, 0), glm::vec3(0.f, 1.f, 1.f)};
    Vertex3D ver2 = Vertex3D(glm::vec3(0.5f, -0.5f, 0), glm::vec3(1.f, 0.f, 1.f));
    Vertex3D ver3 = Vertex3D(glm::vec3(0.5f, 0.5f, 0), glm::vec3(1.f, 1.f, 0.f));
    Vertex3D ver4 = Vertex3D(glm::vec3(-0.5f, 0.5f, 0), glm::vec3(1.f, 1.f, 1.f));
    form.vertices.push_back(ver1);
    form.vertices.push_back(ver2);
    form.vertices.push_back(ver3);
    form.vertices.push_back(ver4);
    form.indices.push_back(0);
    form.indices.push_back(1);
    form.indices.push_back(2);
    form.indices.push_back(0);
    form.indices.push_back(2);
    form.indices.push_back(3);
    form.init();

    Player drone{};

    Wrapper cube{};
    cube.vertices.emplace_back(glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(0.f, 0.f, 0.f));
    cube.vertices.emplace_back(glm::vec3(0.25f, -0.25f, -0.25f), glm::vec3(1.f, 0.f, 0.f));
    cube.vertices.emplace_back(glm::vec3(0.25f, -0.25f, 0.25f), glm::vec3(1.f, 1.f, 0.f));
    cube.vertices.emplace_back(glm::vec3(-0.25f, -0.25f, 0.25f), glm::vec3(0.f, 1.f, 0.f));
    cube.vertices.emplace_back(glm::vec3(-0.25f, 0.25f, -0.25f), glm::vec3(0.f, 0.f, 1.f));
    cube.vertices.emplace_back(glm::vec3(0.25f, 0.25f, -0.25f), glm::vec3(1.f, 0.f, 1.f));
    cube.vertices.emplace_back(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(1.f, 1.f, 1.f));
    cube.vertices.emplace_back(glm::vec3(-0.25f, 0.25f, 0.25f), glm::vec3(0.f, 1.f, 1.f));

    // Face
    cube.indices.push_back(0);
    cube.indices.push_back(1);
    cube.indices.push_back(2);
    cube.indices.push_back(0);
    cube.indices.push_back(2);
    cube.indices.push_back(3);

    // LEFT
    cube.indices.push_back(0);
    cube.indices.push_back(3);
    cube.indices.push_back(4);
    cube.indices.push_back(3);
    cube.indices.push_back(4);
    cube.indices.push_back(7);

    // DOWN
    cube.indices.push_back(0);
    cube.indices.push_back(4);
    cube.indices.push_back(5);
    cube.indices.push_back(0);
    cube.indices.push_back(1);
    cube.indices.push_back(5);

    // Back
    cube.indices.push_back(5);
    cube.indices.push_back(6);
    cube.indices.push_back(7);
    cube.indices.push_back(4);
    cube.indices.push_back(5);
    cube.indices.push_back(7);

    // RIGHT
    cube.indices.push_back(1);
    cube.indices.push_back(2);
    cube.indices.push_back(5);
    cube.indices.push_back(2);
    cube.indices.push_back(5);
    cube.indices.push_back(6);

    // UP
    cube.indices.push_back(2);
    cube.indices.push_back(3);
    cube.indices.push_back(6);
    cube.indices.push_back(3);
    cube.indices.push_back(6);
    cube.indices.push_back(7);

    cube.init();

    Camera    camera{};
    glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f);
    camera.init(&drone, cameraDistance, cameraBaseHeight);

    Model flyingDrone("./assets/drone.gltf");

    ctx.update = [&]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 baseModel = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view      = glm::lookAt(camera.getPosition(), drone.getPosition(), {0, 1, 0});
        shader.use();
        shader.set("projection", projection);
        shader.set("model", baseModel);
        shader.set("view", view);
        form.draw();
        // cube.draw();
        shaderGLTF.use();
        shaderGLTF.set("projection", projection);
        shaderGLTF.set("view", view);
        // glm::mat4 modelC = glm::mat4(1.0);
        //  modelC           = glm::translate(modelC, glm::vec3(-0.2, 0.2, 0.6));
        //  modelC = glm::rotate(modelC, p6::PI, glm::vec3(1.0f, 0.0f, 0.0f));
        //  modelC           = glm::rotate(modelC, -p6::PI / 2.f, glm::vec3(0.0f, 1.0f, 0.0f));
        //  modelC = glm::scale(modelC, glm::vec3(0.03));
        drone.update(shaderGLTF);
        camera.update();
        // shaderGLTF.set("model", modelC);
        shaderGLTF.set("lightColor", glm::vec3(1, 1, 1));
        shaderGLTF.set("lightPosition", glm::vec3(2, 2, 2));
        shaderGLTF.set("camPos", camera.getPosition());
        flyingDrone.Draw(shaderGLTF.id());

        checkInputs(ctx, camera, drone);
    };

    ctx.start();
    form.finish();
}