#version 410 core

out vec4 FragColor;

in vec3 outPos;
in vec3 outColor;
in vec2 outTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    FragColor = texture(texture1, outTexCoord); 
    // FragColor = mix(texture(texture1, outTexCoord), texture(texture2, outTexCoord), 0.5);
    // FragColor = vec4(outColor, 1.0);
    // FragColor = mix(vec4(outColor, 1.0), texture(texture1, outTexCoord), 0.5);
}
