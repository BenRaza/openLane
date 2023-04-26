#include "controls.hpp"
#include "GLFW/glfw3.h"

void checkInputs(p6::Context& ctx, Camera& camera, Player& player)
{
    ///// THIS IS THE CAMERA ///////

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

    ///// THIS IS THE PLAYER ///////

    if (ctx.key_is_pressed(GLFW_KEY_W))
    {
        player.moveForward();
    }
    if (ctx.key_is_pressed(GLFW_KEY_A))
    {
        player.rotateLeft();
    }
    if (ctx.key_is_pressed(GLFW_KEY_S))
    {
        player.moveBackward();
    }
    if (ctx.key_is_pressed(GLFW_KEY_D))
    {
        player.rotateRight();
    }
    if (ctx.key_is_pressed(GLFW_KEY_Q))
    {
        player.moveDown();
    }
    if (ctx.key_is_pressed(GLFW_KEY_SPACE))
    {
        player.moveUp();
    }
}