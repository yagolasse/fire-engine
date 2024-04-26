#version 410 core

out vec4 FragColor;

in vec3 outPos;
in vec3 outColor;
in vec2 outTexCoord;
in vec3 outNormal;
in vec3 outFragmentPosition;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 ambientLightPosition;
uniform vec3 ambientLightColor;
uniform float ambientLightStrenght;

void main() {
    vec3 normal = normalize(outNormal);
    vec3 lightDirection = normalize(ambientLightPosition - outFragmentPosition);
    float diffuseAmount = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diffuseAmount * ambientLightColor;
    vec3 ambientLight = ambientLightColor * ambientLightStrenght;
    FragColor = vec4(ambientLight + diffuse, 1.0) * texture(texture1, outTexCoord) * vec4(outColor, 1.0); 
}
