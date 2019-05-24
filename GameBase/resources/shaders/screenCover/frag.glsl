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

float inf() {
    return 1.0 / 0.0;
}

float neginf() {
    return 1.0 / -0.0;
}

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

void swap(inout float a, inout float b) {
    float c = a;
    a = b;
    b = c;
}

bool rayBox(Ray r, vec3 cubeMin, vec3 cubeMax) {

    vec3 tmin = (cubeMin - r.o) / r.d;
    vec3 tmax = (cubeMax - r.o) / r.d;

    if (tmin.x > tmax.x) swap(tmin.x, tmax.x);
    if (tmin.y > tmax.y) swap(tmin.y, tmax.y);
    if (tmin.z > tmax.z) swap(tmin.z, tmax.z);

    if ((tmin.x > tmax.y) || (tmin.y > tmax.x)) return false;
    if (tmin.y > tmin.x) tmin.x = tmin.y;
    if (tmax.y < tmax.x) tmax.x = tmax.y;

    if ((tmin.x > tmax.z) || (tmin.z > tmax.x)) return false;
    if (tmin.z > tmin.x) tmin.x = tmin.z;
    if (tmax.z < tmax.x) tmax.x = tmax.z;

    if (tmin.x < 0) return false;

    return true;
}

vec4 raycast(Ray r) {
    vec3 cubeMin = vec3(-1, -1, -4);
    vec3 cubeMax = vec3(1, 1, -2);

    if (rayBox(r, cubeMin, cubeMax)) return vec4(1, 0, 1, 1);

    return texture(tex, vec3(uv, 0));
}

void main() {
    float aspect = float(winSize.x) / float(winSize.y);
    vec2 screenPos = (uv * 2 - 1) / vec2(1, aspect);
    color = raycast(Ray(cameraPos, normalize(mat3(cameraRot) * vec3(screenPos, -1.5))));
}