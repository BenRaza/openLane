#include "./wrapper/wrapper.hpp"
#include "glimac/default_shader.hpp"
#include "p6/p6.h"

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    Wrapper         form{};
    struct Vertex3D ver1 = {glm::vec3(-0.5f, -0.5f, 0), glm::vec3(1.f, 1.f, 1.f)};
    Vertex3D        ver2 = Vertex3D(glm::vec3(0.5f, -0.5f, 0), glm::vec3(1.f, 1.f, 1.f));
    Vertex3D        ver3 = Vertex3D(glm::vec3(0.5f, 0.5f, 0), glm::vec3(1.f, 1.f, 1.f));
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

    ctx.update = [&]() {
        glimac::bind_default_shader();
        form.draw();
    };

    ctx.start();
    form.finish();
}