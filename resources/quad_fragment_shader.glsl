#version 430 core

out vec4 FragColor;

uniform sampler2DArray textures;

in vec2 outPos;
in vec4 outColor;
in vec2 outTexCoord;
flat in uint outTextureIndex;

void main() {
    FragColor = texture(textures, vec3(outTexCoord, float(outTextureIndex))) * outColor;
}
