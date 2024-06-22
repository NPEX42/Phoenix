#version 410 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aUV;
layout(location = 3) in int aID;

layout(location = 0) out vec3 vColor;
layout(location = 1) out vec2 vUV;
layout(location = 2) out int vID;

void main() {
	gl_Position = vec4(aPosition, 0.0, 1.0);
	vUV = aUV;
	vColor = aColor;
	vID = aID;
}
