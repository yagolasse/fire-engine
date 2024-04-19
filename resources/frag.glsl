#version 410 core

out vec4 FragColor;

in vec3 outPos;
in vec3 outColor;
in vec2 outTexCoord;

uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, outTexCoord); 
    // FragColor = vec4(outPos + 0.5, 1.0);
    // FragColor = mix(vec4(outColor, 1.0), texture(texture1, outTexCoord), 0.5);
}
