#version 410 core

layout(location = 0) in vec2 vUV;
layout(location = 1) in vec3 vNormal;

layout(location = 0) out vec4 fragColor;
uniform vec4 uTint;

void main() {
    fragColor = uTint;
}
