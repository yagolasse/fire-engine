#version 410

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scaling;

out vec3 outPos;

void main() {
    mat4 model = translation * rotation * scaling;
    vec4 transform = model * vec4(aPos, 1.0);
    gl_Position = projection * view * transform;
    outPos = aPos;
}
