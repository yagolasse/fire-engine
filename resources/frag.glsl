#version 410 core

out vec4 FragColor;

in vec3 outPos;

void main() {
    FragColor = vec4(outPos + 0.5, 1.0);
}
