#version 450

in vec2 uv;

out vec4 color;

uniform ivec2 winSize;
uniform float t;

struct Ray {
    vec3 o;
    vec3 d;
};

struct Sphere {
    vec3 c;
    float r;
};

struct RayHitInfo {
    float t;
    vec3 p;
    vec3 n;
};

bool raySphere(Ray r, Sphere s, inout RayHitInfo info) {
    vec3 L = r.o - s.c;
    float a = dot(r.d, r.d);
    float b = 2 * dot(r.d, L);
    float c = dot(L, L) - s.r * s.r;
    float disc = b * b - 4 * a * c;
    float t0, t1;
    if (disc < 0) return false;
    else if (disc == 0) t0 = t1 = -0.5 * b / a;
    else {
        float q = (b > 0) ? -0.5 * (b + sqrt(disc)) : -0.5 * (b - sqrt(disc));
        t0 = q / a;
        t1 = c / q;
    }
    if (t0 > t1) {
        float tmp = t0;
        t0 = t1;
        t1 = tmp;
    }
    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return false;
    }
    info.t = t0;
    info.p = r.o + r.d * t0;
    info.n = normalize(s.c - info.p);
    return true;
}

void main() {
    float aspect = float(winSize.y) / float(winSize.x);
    vec2 screenPos = uv * 2 - 1;
    screenPos.y *= -aspect;

    RayHitInfo info;
    Ray ray = { vec3(0, 0, 0), normalize(vec3(screenPos.x, screenPos.y, -1.5)) };
    Sphere sphere = { vec3(0, 0, -4), 1 };
    bool hit = raySphere(ray, sphere, info);

    float l = max(0.f, dot(info.n, normalize(vec3(t, 0, 0) - info.p)));

    color = hit ? vec4(vec3(1, 0, 1) * l, 1) : vec4(0, 0, 0, 1);
}