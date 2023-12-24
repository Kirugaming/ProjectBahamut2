#version 460 core
out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 colors;

void main()
{
    if (texture(texture_diffuse1, texCoords).r > 0.0) {
        fragColor = texture(texture_diffuse1, texCoords);
    } else {
        fragColor = vec4(colors, 1.0);
    }

}