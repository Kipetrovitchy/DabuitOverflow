#version 330 core

/* Structures */
struct Light
{
    int  type; // Type of lights 0 : directional, 1 : point, 2 : spot
    vec3 direction;
    vec3 position;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material
{
    bool        isAmbientMap;
    sampler2D   ambientMap;
    vec3        ambient;

    bool        isDiffuseMap;
    sampler2D   diffuseMap;
    vec3        diffuse;

    bool        isSpecularMap;
    sampler2D   specularMap;
    vec3        specular;

    float       shininess;
};

/* Values in */
in VertexData {
    vec4 position;
    vec3 uv;
    vec3 normal;
} i;

#define MAX_LIGHT 50
/* Values out */
uniform sampler2D   text;
uniform vec3        viewPos;
uniform uint        nLights;
uniform Light[MAX_LIGHT] lights;
uniform Material    material;

/* Uniform values */
out vec4 fragColor;

void main()
{
	fragColor = texture(material.diffuseMap, vec2(i.uv));
}
