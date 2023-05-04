#include "Texture.h"
#include <iostream>
#include <utility>

GLuint loadTexture(std::filesystem::path texture_path)
{
    const img::Image image = p6::load_image_buffer(std::move(texture_path));

    GLuint texture_id = 0;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}

Texture::Texture(const char* image, const char* texType)
{
    type = texType;
    // glActiveTexture(GL_TEXTURE0);
    ID = loadTexture(image);
    // glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::texUnit(GLuint shaderId, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shaderId, uniform);
    // Shader needs to be activated before changing the value of a uniform
    // shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, 0);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}