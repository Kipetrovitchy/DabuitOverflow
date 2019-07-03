#version 330 core
in vec2 TexCoords;
out vec4 fcolor;

uniform sampler2D text;
uniform vec4 color;

void main()
{    
    vec4 sampled = color * vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);

    if(sampled.a == 0.0)
        discard;
    fcolor = sampled;
    
}  