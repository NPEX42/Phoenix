#version 410 core

layout(location = 0) in vec3 vColor;
layout(location = 1) in vec2 vUV;

layout(location = 0) out vec4 fragColor;

void main() {
	fragColor = vec4(vUV, 1.0, 1.0);
}
