#version 410 core

out vec4 FragColor;

in vec3 outPos;
in vec3 outColor;
in vec2 outTexCoord;
in vec3 outNormal;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 ambientLightColor;
uniform float ambientLightStrenght;

void main() {
    vec3 ambientLight = ambientLightColor * ambientLightStrenght;
    FragColor = vec4(ambientLight, 1.0) * texture(texture1, outTexCoord); 
}
