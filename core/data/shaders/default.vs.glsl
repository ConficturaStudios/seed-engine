#version 400 core

in vec3 position;
in vec3 normal;
in vec2 tex_coords;

out vec3 frag_position;
out vec2 frag_tex_coords;
out vec3 frag_normal;
out vec3 frag_to_camera;
/*
layout (std140) uniform ShaderVertexData {
    mat4 transformation_mat;
    mat4 projection_mat;
    mat4 view_mat;
};*/
uniform mat4 transformation_mat;
uniform mat4 projection_mat;
uniform mat4 view_mat;

void main(void) {
    vec4 world_position = transformation_mat * vec4(position, 1.0);
    gl_Position = projection_mat * view_mat * world_position;
    frag_position = gl_Position.xyz;
    frag_tex_coords = tex_coords;
    frag_normal = (transformation_mat * vec4(normal, 0.0)).xyz;
    frag_to_camera = normalize(world_position.xyz - (view_mat * vec4(0.0, 0.0, 0.0, 1.0)).xyz);
}