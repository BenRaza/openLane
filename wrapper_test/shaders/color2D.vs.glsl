#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  vFragColor = aVertexColor;
  gl_Position = projection * view * model * vec4(aVertexPosition, 1);
};