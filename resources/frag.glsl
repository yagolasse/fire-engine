#version 410 core

out vec4 FragColor;

in vec3 outPos;
in vec2 outTexCoord;

uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, outTexCoord); // vec4(outPos + 0.5, 1.0);
}
