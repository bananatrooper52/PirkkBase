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

__kernel void renderRaytrace(__global float4* output, int width, int height) {
    const int workItemId = get_global_id(0);
    float2 screenPos = floor((float2)(workItemId % width, workItemId / width)) / (float)(max(width, height));
    output[workItemId] = (float4)(screenPos, 0.f, 1.f);
}