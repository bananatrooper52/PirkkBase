#version 450

#define MAX_SPHERES 128
#define REFLECTION_LIMIT 8

struct Ray {
    vec3 o;
    vec3 d;
};

struct Sphere {
    vec3 c;
    float r;
    vec3 color;
    float emission;
};

in vec2 uv;

out vec4 color;

uniform ivec2 winSize;
uniform float t;
uniform Sphere spheres[MAX_SPHERES];
uniform int sphereCount;
uniform vec3 cameraPos;
uniform mat4 cameraRot;

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

float smin(float a, float b, float k = 32) {
    float res = exp2(-k * a) + exp2(-k * b);
    return -log2(res) / k;
}

float sphereDist(vec3 p) {
    float v = 0;
    for (int i = 0; i < sphereCount; i++) {
        float dist = distance(p, spheres[i].c) - spheres[i].r;
        v = i == 0 ? 
            dist : 
            smin(v, dist, 8);
    }
    return v;
}

float torusDist(vec3 p) {
    float v = 0;
    for (int i = 0; i < sphereCount; i++) {
        vec3 p0 = p - spheres[i].c;
        vec2 t = vec2(0.5, 0.25);
        vec2 q = vec2(length(p0.xz) - t.x, p0.y);
        float dist = length(q) - t.y;
        v = i == 0 ? 
            dist : 
            smin(v, dist, 32);
    }
    return v;
}

float cubeDist(vec3 p) {
    float v = 0;
    for (int i = 0; i < sphereCount; i++) {
        vec3 p0 = p - spheres[i].c;
        vec3 b = vec3(spheres[i].r);
        vec3 d = abs(p0) - b;
        float dist = length(max(d, 0)) + min(max(d.x, max(d.y, d.z)), 0);
        v = i == 0 ? 
            dist : 
            smin(v, dist, 32);
    }
    return v;
}

vec3 getNormal(vec3 p) {
    const vec2 h = vec2(0.01, 0);
    return normalize(vec3(
            cubeDist(p + h.xyy) - cubeDist(p - h.xyy),
            cubeDist(p + h.yxy) - cubeDist(p - h.yxy),
            cubeDist(p + h.yyx) - cubeDist(p - h.yyx)
    ));
}

vec4 raycast(Ray r) {
    // Distance of the full ray
    float rdist = 0;
    for (int i = 0; i < 100; i++) {
        float dist = cubeDist(r.o);
        rdist += dist;
        if (dist < 0.01) {
            vec3 n = getNormal(r.o);
            float l = max(0, dot(n, vec3(0, 1, 0)));
            return vec4(n * l, 0);
        }
        r.o += r.d * dist;
    }
    return vec4(0, 0, 0, 0);
}

void main() {
    float aspect = float(winSize.x) / float(winSize.y);
    vec2 screenPos = uv * 2 - 1;
    screenPos.x *= aspect;

    Ray ray = { cameraPos, normalize(vec3(screenPos.x, screenPos.y, -1.5)) * mat3(cameraRot) };

    color = raycast(ray);
}