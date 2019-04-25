struct Ray {
    float3 o;
    float3 d;
};

struct Sphere {
    float3 c;
    float r;
    float3 color;
    float3 emission;
};

struct RayHitInfo {
    float t;
    float3 p;
    float3 n;
};

void swap(void *a, void *b) {
    void *c = a;
    a = b;
    b = c;
}

bool raySphere(struct Ray r, struct Sphere s, struct RayHitInfo *out) {
    float3 L = r.o - s.c;
    float a = dot(r.d, r.d);
    float b = 2 * dot(r.d, L);
    float c = dot(L, L) - s.r * s.r;
    float disc = b * b - 4 * a * c;
    float t0, t1;
    if (disc < 0) return false;
    else if (disc == 0) t0 = t1 = -0.5f * b / a;
    else {
        float q = (b > 0) ? -0.5f * (b + sqrt(disc)) : -0.5f * (b - sqrt(disc));
        t0 = q / a;
        t1 = c / q;
    }
    if (t0 > t1) swap(&t0, &t1);
    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return false;
    }
    out->t = t0;
    out->p = r.o + r.d * t0;
    out->n = normalize(s.c - out->p);
    return true;
}

__kernel void renderRaytrace(__global float4* output, int width, int height, float t) {
    const int workItemId = get_global_id(0);
    float aspect = (float)height / (float)width;
    int2 pixelPos = (int2)(workItemId % width, workItemId / width);
    float2 screenPos = (float2)((float)pixelPos.x / (float)width, (float)pixelPos.y / (float)height) * 2.f - 1.f;
    screenPos.y *= -aspect;

    struct RayHitInfo out;
    struct Ray ray = { (float3)(0, 0, 0), normalize((float3)(screenPos.x, screenPos.y, -1.5f)) };
    struct Sphere sphere = { (float3)(0, 0, -4), 1 };
    bool hit = raySphere(ray, sphere, &out);

    float l = max(0.f, dot(out.n, normalize((float3)(t, 0, 0) - out.p)));

    output[workItemId] = hit ? (float4)((float3)(1, 0, 1) * l, 1) : (float4)(0, 0, 0, 1);
}