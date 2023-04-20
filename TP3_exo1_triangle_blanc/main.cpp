#include "glimac/default_shader.hpp"
#include "p6/p6.h"

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    const GLuint VERTEX_ATTR_POSITION = 0;

    GLuint vbo = 0;
    GLuint vao = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    std::array<GLfloat, 6> vertices = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), &vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glimac::bind_default_shader();

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}