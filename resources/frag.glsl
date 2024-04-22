#version 410 core

out vec4 FragColor;

in vec3 outPos;
in vec3 outColor;
in vec2 outTexCoord;

uniform sampler2D texture;
// uniform sampler2D texture2;

void main() {
    FragColor = texture(texture, outTexCoord); 
    // FragColor = mix(texture(texture1, outTexCoord), texture(texture2, outTexCoord), 0.5);
    // FragColor = vec4(outColor, 1.0);
    // FragColor = vec4(0.0, outTexCoord, 1.0);
    // FragColor = mix(vec4(outColor, 1.0), texture(texture1, outTexCoord), 0.5);
}
