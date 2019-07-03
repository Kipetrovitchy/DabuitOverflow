#version 330 core

/* Values in */
layout (location = 0) in vec4 i_position;
layout (location = 1) in vec3 i_uv;
layout (location = 2) in vec3 i_normal;

/* Uniform values */
struct Transformation {
    mat4 viewMat;
    mat4 model;
    mat3 inverseModel;
} u;

uniform Transformation transform;

/* Values out */
out VertexData {
    vec4 position;
    vec3 uv;
    vec3 normal;
} o;

void main()
{
    // Get the position of the vertex in the real model
    o.position = transform.model * i_position;

    // Set the position to openGL
    gl_Position = transform.viewMat * transform.model * i_position; // A tester model * position -> fragPos

    // Give the texture coordinates and the normal to the fragment shader
    o.uv = i_uv;

    o.normal = transform.inverseModel * i_normal;
}
