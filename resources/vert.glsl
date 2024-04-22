#version 410

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 outPos;
out vec3 outColor;
out vec2 outTexCoord;

void main() {
    // projection * view * model *
    gl_Position =  vec4(aPos, 1.0);
    outPos = aPos;
    outColor = aColor;
    outTexCoord = aTexCoord;
}
