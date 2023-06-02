#include "wrapper.hpp"
#include <array>
#include <vector>

void Wrapper::init()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (!indices.empty())
    {
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    if (!indices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    }
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int cubemapTexture;
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    addVertices();
    addIndices();
}

void Wrapper::draw()
{
    glBindVertexArray(vao);
    if (indices.empty())
    {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }
    else
    {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    }
    glBindVertexArray(0);
}

void Wrapper::finish()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Wrapper::addVertices()
{
    vertices.emplace_back(-20.0f, -20.0f, 20.0f);
    vertices.emplace_back(20.0f, -20.0f, 20.0f);
    vertices.emplace_back(20.0f, -20.0f, -20.0f);
    vertices.emplace_back(-20.0f, -20.0f, -20.0f);
    vertices.emplace_back(-20.0f, 20.0f, 20.0f);
    vertices.emplace_back(20.0f, 20.0f, 20.0f);
    vertices.emplace_back(20.0f, 20.0f, -20.0f);
    vertices.emplace_back(-20.0f, 20.0f, -20.0f);
}

void Wrapper::addIndices()
{
    // Right
    indices.emplace_back(1);
    indices.emplace_back(2);
    indices.emplace_back(6);
    indices.emplace_back(6);
    indices.emplace_back(5);
    indices.emplace_back(1);

    // Left
    indices.emplace_back(0);
    indices.emplace_back(4);
    indices.emplace_back(7);
    indices.emplace_back(7);
    indices.emplace_back(3);
    indices.emplace_back(0);

    // Top
    indices.emplace_back(4);
    indices.emplace_back(5);
    indices.emplace_back(6);
    indices.emplace_back(6);
    indices.emplace_back(7);
    indices.emplace_back(4);

    // Bottom
    indices.emplace_back(0);
    indices.emplace_back(3);
    indices.emplace_back(2);
    indices.emplace_back(2);
    indices.emplace_back(1);
    indices.emplace_back(0);

    // Front
    indices.emplace_back(3);
    indices.emplace_back(7);
    indices.emplace_back(6);
    indices.emplace_back(6);
    indices.emplace_back(2);
    indices.emplace_back(3);
}