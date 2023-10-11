#version 460 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;

out vec2 texCoords;

uniform mat4 model;

void main() {
    texCoords = inTexCoords;
    gl_Position = model * vec4(inPos, 1.0);
}