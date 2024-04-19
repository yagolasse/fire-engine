#version 410

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 transform;

out vec3 outPos;
out vec2 outTexCoord;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    outPos = aPos;
    outTexCoord = aTexCoord;
}
