#version 410

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 outPos;
out vec3 outColor;
out vec2 outTexCoord;
out vec3 outNormal;
out vec3 outFragmentPosition;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    outFragmentPosition = vec3(model * vec4(aPos, 1.0));

    outPos = aPos;
    outColor = aColor;
    outTexCoord = aTexCoord;
    outNormal = aNormal;
}
