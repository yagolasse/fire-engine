#version 410 core

out vec4 FragColor;

uniform sampler2D texture1;

in vec2 outPos;
in vec4 outColor;
in vec2 outTexCoord;

void main() {
    FragColor = texture(texture1, outTexCoord) * outColor;
}
