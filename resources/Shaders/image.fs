#version 330 core
in vec2 TexCoords;
out vec4 fcolor;

uniform sampler2D text;
uniform vec4 color;

void main()
{    
    vec4 textureColored = texture(text, TexCoords) * color;

    if (textureColored.a == 0)
        discard;

    fcolor = textureColored;
}  