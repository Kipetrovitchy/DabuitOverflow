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

/* Functions */
vec3  computeLight      (uint n, vec3 normal, vec3 viewDir);
vec3  computeDirLight   (uint n, vec3 normal, vec3 viewDir);
vec3  computePointLight (uint n, vec3 normal, vec3 viewDir);
vec3  computeSpotLight  (uint n, vec3 normal, vec3 viewDir);
vec3  getAmbient        (uint n);
vec3  getDiffuse        (uint n, vec3 normal, vec3 lightDir);
vec3  getSpecular       (uint n, vec3 normal, vec3 viewDir, vec3 lightDir);

void main()
{
    vec3    norm        = normalize(i.normal);
    vec3    viewDir     = normalize(viewPos - vec3(i.position));

    vec3    exit = vec3(0.0);
    uint n;
    for (n = 0u; n < nLights; n++)
    {
        exit += computeLight(n, norm, viewDir);
    }

    fragColor = vec4(exit, 1.0);
}

vec3 computeLight(uint n, vec3 normal, vec3 viewDir)
{
    vec3 exit = vec3(0.0);

    switch (lights[n].type)
    {
        case 0: exit = computeDirLight(n, normal, viewDir);    break;
        case 1: exit = computePointLight(n, normal, viewDir);  break;
        case 2: exit = computeSpotLight(n, normal, viewDir);   break;
        default: break;
    }

    return exit;
}

vec3 computeDirLight(uint n, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-lights[n].direction);

    // combine results
    vec3    ambient     = getAmbient(n);
    vec3    diffuse     = getDiffuse(n, normal, lightDir);
    vec3    specular    = getSpecular(n, normal, viewDir, lightDir);

    return (ambient + diffuse + specular);
}

vec3 computePointLight(uint n, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(lights[n].position - vec3(i.position));

    // combine results
    vec3    ambient     = getAmbient(n);
    vec3    diffuse     = getDiffuse(n, normal, lightDir);
    vec3    specular    = getSpecular(n, normal, viewDir, lightDir);

    // attenuation
    float dist        = length(lights[n].position - vec3(i.position));
    float attenuation = 1.0 / (lights[n].constant + lights[n].linear * dist +
        lights[n].quadratic * (dist * dist));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 computeSpotLight(uint n, vec3 normal, vec3 viewDir)
{
    // Compute all the values for the different lights (diffuse and spec)
    vec3    lightDir    = normalize(lights[n].position - vec3(i.position));

    // Get the components of the light
    vec3    ambient     = getAmbient(n);

    // spotlight (soft edges)
    float theta     = dot(lightDir, normalize(-lights[n].direction));
    if (theta > lights[n].outerCutOff)
    {
        // Get the components of the light
        vec3    diffuse     = getDiffuse(n, normal, lightDir);
        vec3    specular    = getSpecular(n, normal, viewDir, lightDir);
        // Values of the spotlight
        float epsilon   = (lights[n].cutOff - lights[n].outerCutOff);
        float intensity = clamp((theta - lights[n].outerCutOff) / epsilon, 0.0, 1.0);

        diffuse  *= intensity;
        specular *= intensity;

        return (ambient + diffuse + specular);
    }

    return ambient;
}

vec3 getAmbient(uint n)
{
    if (material.isAmbientMap)
        return lights[n].ambient * vec3(texture(material.ambientMap, vec2(i.uv)));
    else if (material.isDiffuseMap)
        return lights[n].ambient * vec3(texture(material.diffuseMap, vec2(i.uv)));
    else
        return lights[n].ambient * material.ambient;
}

vec3 getDiffuse(uint n, vec3 normal, vec3 lightDir)
{
    // Get the coefficiant of the diffuse lights
    float   diff = max(dot(normal, lightDir), 0.0);

    // return the diffuse light
    if (material.isDiffuseMap)
        return lights[n].diffuse * (diff * vec3(texture(material.diffuseMap, vec2(i.uv))));
    else
        return lights[n].diffuse * (diff * material.diffuse);
}

vec3 getSpecular(uint n, vec3 normal, vec3 viewDir, vec3 lightDir)
{
    // Get the reflection
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // Get the coeficiant fo the specular
    float   spec        = pow(
        max(dot(normal, halfwayDir), 0.0),
        material.shininess
    );

    // return the specular light
    if (material.isSpecularMap)
        return lights[n].specular *
                (spec * vec3(texture(material.specularMap, vec2(i.uv))));
    else
        return lights[n].specular * (spec * material.specular);
}
