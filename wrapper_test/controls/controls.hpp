#pragma once

#include "../camera/camera.hpp"

void checkInputs(p6::Context& ctx, Camera& camera)
{
    if (ctx.key_is_pressed(GLFW_KEY_LEFT))
    {
        camera.rotateLeft();
    }
    if (ctx.key_is_pressed(GLFW_KEY_RIGHT))
    {
        camera.rotateRight();
    }
    if (ctx.key_is_pressed(GLFW_KEY_UP))
    {
        camera.rotateUp();
    }
    if (ctx.key_is_pressed(GLFW_KEY_DOWN))
    {
        camera.rotateDown();
    }
}