#version 410

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

layout(location = 0) out vec2 vUV;
layout(location = 1) out vec3 vNormal;

uniform mat4 uVP;
uniform mat4 uModelMat;

void main() {
	gl_Position = uVP * uModelMat * vec4(aPosition, 1.0);
    vUV = aUV;
    vNormal = (uModelMat * vec4(aNormal, 1.0)).xyz;
}

