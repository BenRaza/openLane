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
    if (ctx.key_is_pressed(GLFW_KEY_TAB))
    {
        camera.lockCamera();
    }
    ctx.mouse_scrolled = [&camera](p6::MouseScroll event) {
        std::cout << event.dy << std::endl;
        if (event.dy == 1)
        {
            camera.moveCloser();
        }
        if (event.dy == -1)
        {
            camera.moveAway();
        }
    };

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