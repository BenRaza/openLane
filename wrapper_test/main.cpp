// #include "GLFW/glfw3.h"
#include "camera/camera.hpp"
#include "glimac/default_shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
// #include "src-common/glimac/sphere_vertices.hpp"
#include "wrapper/wrapper.hpp"

int main()
{
    glm::mat4 projection = glm::perspective(glm::radians(45.f), static_cast<float>(1280) / static_cast<float>(720), 0.001f, 100.0f);
    glm::mat4 model      = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    float cameraDistance   = 2;
    float cameraBaseHeight = 1;

    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    const p6::Shader shader = p6::load_shader(
        "shaders/color2D.vs.glsl",
        "shaders/color2D.fs.glsl"
    );

    // const std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16);

    Wrapper form{};
    // for (vertice : vertices)
    struct Vertex3D ver1 = {glm::vec3(-0.5f, -0.5f, 0), glm::vec3(0.f, 1.f, 1.f)};
    Vertex3D        ver2 = Vertex3D(glm::vec3(0.5f, -0.5f, 0), glm::vec3(1.f, 0.f, 1.f));
    Vertex3D        ver3 = Vertex3D(glm::vec3(0.5f, 0.5f, 0), glm::vec3(1.f, 1.f, 0.f));
    Vertex3D        ver4 = Vertex3D(glm::vec3(-0.5f, 0.5f, 0), glm::vec3(1.f, 1.f, 1.f));
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

    Camera camera{};
    camera.init(glm::vec3(0.f, 0.f, 0.f), cameraDistance, cameraBaseHeight);
    std::cout << camera.getPosition().x << " " << camera.getPosition().y << " " << camera.getPosition().z << std::endl;

    ctx.update = [&]() {
        // glimac::bind_default_shader();
        glClear(GL_COLOR_BUFFER_BIT);
        glm::mat4 view = glm::lookAt(camera.getPosition(), camera.getTarget(), {0, 1, 0});
        // model          = glm::translate(model, glm::vec3(0.f, 0.f, -0.005f));
        shader.use();
        shader.set("projection", projection);
        shader.set("model", model);
        shader.set("view", view);
        form.draw();

        // if (ctx.key_is_pressed(GLFW_KEY_LEFT_CONTROL))
        // {
        //     std::cout << "bibop" << std::endl;
        // }

        // shader.set("model2", model);
        // form2.draw();
    };

    ctx.start();
    form.finish();
}