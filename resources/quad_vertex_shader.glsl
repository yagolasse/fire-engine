#version 410

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
// layout (location = 2) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 projection;

out vec2 outPos;
out vec4 outColor;
// out vec2 outTexCoord;

void main() {
    // 
    gl_Position = projection * view * vec4(aPos, 0.0, 1.0);
    outPos = aPos;
    outColor = aColor;
    // outTexCoord = aTexCoord;
}
