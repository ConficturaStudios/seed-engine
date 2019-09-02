#version 400 core
layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gColor;
layout (location = 3) out vec4 gRSMAo;
layout (location = 4) out vec4 gCamera;

out vec4 color;

in vec3 frag_position;
in vec2 frag_tex_coords;
in vec3 frag_normal;
in vec3 frag_to_camera;

// uniform sampler2D tex_sample_0;
// uniform sampler2D tex_sample_1;
// uniform sampler2D tex_sample_2;
// uniform sampler2D tex_sample_3;
// uniform sampler2D tex_sample_4;
// uniform sampler2D tex_sample_5;
// uniform sampler2D tex_sample_6;
// uniform sampler2D tex_sample_7;
// uniform sampler2D tex_sample_8;
// uniform sampler2D tex_sample_9;
// uniform sampler2D tex_sample_10;
// uniform sampler2D tex_sample_11;
// uniform sampler2D tex_sample_12;
// uniform sampler2D tex_sample_13;
// uniform sampler2D tex_sample_14;
// uniform sampler2D tex_sample_15;

vec4 diffuse;
float roughness;
float specular;
float metallic;
float ambient_occlusion;

void compute() {

}

void main(void) {
    diffuse = vec4(0.0, 1.0, 0.0, 1.0);
    roughness = 0.5;
    specular = 0.5;
    metallic = 0.5;
    ambient_occlusion = 0.5;
    compute();
    gPosition = vec4(frag_position, gl_FragDepth);
    gNormal = vec4(normalize(frag_normal), 1.0);
    gColor = diffuse;
    gRSMAo = vec4(roughness, specular, metallic, ambient_occlusion);
    gCamera = vec4(frag_to_camera, 1.0);
    color = gColor;
}