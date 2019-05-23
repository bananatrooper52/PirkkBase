#version 450

#define MAX_SPHERES 128
#define REFLECTION_LIMIT 8

struct Ray {
    vec3 o;
    vec3 d;
};

in vec2 uv;

out vec4 color;

uniform ivec2 winSize;
uniform vec3 cameraPos;
uniform mat4 cameraRot;

uniform sampler3D tex;

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

vec4 raycast(Ray r) {
    return texture(tex, vec3(uv, 0));
}

void main() {
    color = raycast(Ray(vec3(0, 0, 0), vec3(0, 0, 0)));
}