#version 450

#define CHUNK_SIZE 32

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

void swap(inout float a, inout float b) {
    float c = a;
    a = b;
    b = c;
}

bool rayBox(Ray r, vec3 cubeMin, vec3 cubeMax, inout float t) {

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
    
    t = tmin.x;

    return true;
}

float intbound(float s, float ds) {
    return ds > 0 ? (ceil(s) - s) / ds : (s - floor(s)) / -ds;
}

bool pointInside(vec3 aabbMin, vec3 aabbMax, vec3 p) {
    return
        p.x > aabbMin.x && p.x < aabbMax.x &&
        p.y > aabbMin.y && p.y < aabbMax.y &&
        p.z > aabbMin.z && p.z < aabbMax.z;
}

vec4 raycast(Ray r) {
    vec3 cubeMin = vec3(0, 0, 0);
    vec3 cubeMax = vec3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);

    float t = 0;

    vec3 color = vec3(0.4, 0.4, 0.4);

    if (pointInside(cubeMin, cubeMax, r.o) || rayBox(r, cubeMin, cubeMax, t)) {
        float voxelSize = 0.1;

        vec3 enterPos = (r.o + r.d * t) / voxelSize;

        ivec3 currPos = ivec3(floor(enterPos));
        
        ivec3 s = ivec3(
            r.d.x >= 0 ? 1 : -1,
            r.d.y >= 0 ? 1 : -1,
            r.d.z >= 0 ? 1 : -1
        );

        vec3 bound = currPos + s;
        vec3 tmax = vec3(
            intbound(enterPos.x, r.d.x),
            intbound(enterPos.y, r.d.y),
            intbound(enterPos.z, r.d.z)
        );
        vec3 tdelta = 1.0 / r.d * vec3(s);

        for (int i = 0; i < CHUNK_SIZE * 3; i++) {
            if (tmax.x < tmax.y) {
                if (tmax.x < tmax.z) {
                    currPos.x += s.x;
                    tmax.x += tdelta.x;
                } else {
                    currPos.z += s.z;
                    tmax.z += tdelta.z;
                }
            } else {
                if (tmax.y < tmax.z) {
                    currPos.y += s.y;
                    tmax.y += tdelta.y;
                } else {
                    currPos.z += s.z;
                    tmax.z += tdelta.z;
                }
            }

            vec4 currColor = texture(tex, vec3(currPos) / 32.0) * vec4(1, 1, 1, 0.5);
            if (currColor.a > 0.1) {
                color = vec3(currPos) / 32;
                break;
            }
        }
    }

    return vec4(color, 1);
}

void main() {
    float aspect = float(winSize.x) / float(winSize.y);
    vec2 screenPos = (uv * 2 - 1) / vec2(1, aspect);
    color = raycast(Ray(cameraPos, normalize(mat3(cameraRot) * vec3(screenPos, -1.5))));
}