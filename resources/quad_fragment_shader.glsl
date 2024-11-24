#version 410 core

out vec4 FragColor;

uniform sampler3D textures;

in vec2 outPos;
in vec4 outColor;
in vec2 outTexCoord;

void main() {
    FragColor = texture(textures, vec3(outTexCoord, 2.0f)) * outColor;
}
