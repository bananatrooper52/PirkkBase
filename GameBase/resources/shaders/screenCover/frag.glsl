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
            smin(v, dist, 4);
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
            sphereDist(p + h.xyy) - sphereDist(p - h.xyy),
            sphereDist(p + h.yxy) - sphereDist(p - h.yxy),
            sphereDist(p + h.yyx) - sphereDist(p - h.yyx)
    ));
}

vec3 aabbMin = vec3(0), aabbMax = vec3(0);

vec4 raycast(Ray r) {
    
    // Distance of the full ray
    float rdist = 0;
    for (int i = 0; i < 50; i++) {


        float dist = sphereDist(r.o);

        vec3 p = r.o + r.d * dist;

        if (
            p.x < aabbMin.x ||
            p.y < aabbMin.y ||
            p.z < aabbMin.z ||

            p.x > aabbMax.x ||
            p.y > aabbMax.y ||
            p.z > aabbMax.z
        ) break;

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

    // Calculate bounding box of spheres
    for (int i = 0; i < sphereCount; i++) {
        vec3 scMin = spheres[i].c - spheres[i].r;
        vec3 scMax = spheres[i].c + spheres[i].r;
        if (i == 0) {
            aabbMin = scMin;
            aabbMax = scMax;
        }
        if (scMin.x < aabbMin.x) aabbMin.x = scMin.x;
        if (scMin.y < aabbMin.y) aabbMin.y = scMin.y;
        if (scMin.z < aabbMin.z) aabbMin.z = scMin.z;
        
        if (scMax.x > aabbMax.x) aabbMax.x = scMax.x;
        if (scMax.y > aabbMax.y) aabbMax.y = scMax.y;
        if (scMax.z > aabbMax.z) aabbMax.z = scMax.z;
    }

    float aspect = float(winSize.x) / float(winSize.y);
    vec2 screenPos = uv * 2 - 1;
    screenPos.x *= aspect;

    Ray ray = { cameraPos, normalize(vec3(screenPos.x, screenPos.y, -1.5)) * mat3(cameraRot) };

    color = raycast(ray);
}