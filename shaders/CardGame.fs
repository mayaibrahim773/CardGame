#version 460 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec3 objectColor;
uniform sampler2D texture_diffuse1;
uniform bool useTexture;

void main()
{
    if (useTexture)
    {
        FragColor = texture(texture_diffuse1, texCoord)
                  * vec4(objectColor, 1.0);
    }
    else
    {
        FragColor = vec4(objectColor, 1.0);
    }
}