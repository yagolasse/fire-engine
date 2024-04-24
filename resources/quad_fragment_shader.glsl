#version 410 core

out vec4 FragColor;

in vec2 outPos;
in vec4 outColor;
// in vec2 outTexCoord;

void main() {
    FragColor = outColor;
}
