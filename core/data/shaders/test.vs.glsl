#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 vertex_color_0;
layout(location = 3) in vec2 uv_0;

out vec4 frag_color;

uniform mat4 transformation_mat;
uniform mat4 projection_mat;
uniform mat4 view_mat;

void main()
{
    vec4 world_position = transformation_mat * vec4(position, 1.0);
    vec4 test_pos = projection_mat * view_mat * world_position;
    //gl_Position = vec4(position, 1.0);
    gl_Position = test_pos;
    frag_color = vertex_color_0;
}