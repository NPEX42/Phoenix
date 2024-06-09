#version 410 core

layout(location = 0) in vec3 vColor;
layout(location = 1) in vec2 vUV;

layout(location = 0) out vec4 fragColor;

uniform sampler2D uAlbedo; 

void main() {
	fragColor = vec4(vColor, 1.0) * texture(uAlbedo, vUV);
	if (fragColor.a < 0.5) {
		discard;
	}
}
