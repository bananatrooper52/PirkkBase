#version 450

// Transformation matrix to position camera from pos(0, 0, 0), dir(0, 0, -1)
uniform vec3 cameraPos;
uniform mat4 cameraRot;

// Position of the pixel on the screen (adjusted for aspect ratio, x is always normal)
in vec2 screenPos;

// Final pixel out color
out vec4 color;

// How many reflections are allowed
const int iterationLimit = 3;

struct CollisionInfo {
    bool colliding;
    vec3 position;
    vec3 normal;
};

struct Ray {
    vec3 o;
    vec3 d;
};

struct Sphere {
    vec3 c;
    float r;
};

float rand(float co){
    return fract(sin(co * 12.9898) * 43797.5453);
}

void swap(inout float a, inout float b) {
    float c = a;
    a = b;
    b = c;
}

bool raySphere(Ray ray, Sphere sphere, inout CollisionInfo info) {
    float t0, t1;

    vec3 L = sphere.c - ray.o;
    float tca = dot(L, ray.d);
    if (tca < 0) return false;
    float d2 = dot(L, L) - tca * tca;
    float r2 = sphere.r * sphere.r;
    if (d2 > r2) return false;
    float thc = sqrt(r2 - d2);

    t0 = tca - thc;
    t1 = tca + thc;

    if (t0 > t1) swap(t0, t1);
    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) return false;
    }
    
    info.position = ray.o + ray.d * t0;
    info.normal = normalize(info.position - sphere.c);

    return true;
}

Sphere spheres[64];
vec3 light = vec3(2, 2, 2);

vec4 castRay(Ray r) {

    Ray ray = r;
    vec4 color = vec4(0.5, 0.6, 0.7, 1);
    bool firstHit = true;
    
    for (int i = 0; i < iterationLimit; i++) {
        CollisionInfo info;
        bool hit = false;
        float minDist = 0;
        CollisionInfo minInfo;
        int iout = 0;

        for (int i = 0; i < 64; i++) {
            if (raySphere(ray, spheres[i], info)) {
                float dist = dot(info.position - ray.o, info.position - ray.o);
                if (!hit || dist < minDist) {
                    minDist = dist;
                    minInfo = info;
                    hit = true;
                    iout = i;
                }
            }
        }

        if (!hit) break;
        
        vec3 lightDir = normalize(light - info.position);
        float cosTheta = clamp(dot(minInfo.normal, lightDir) * 6, 0, 1);
        color = mix(color, vec4(vec3(rand(iout * 3), rand(iout * 3 + 1), rand(iout * 3 + 2)), 1), firstHit ? 1 : 0.1) * cosTheta;
        firstHit = false;
        ray.o = minInfo.position;
        ray.d = reflect(ray.d, minInfo.normal);
    }

    return color;
}

void main() {
    for (int i = 0; i < 64; i++) {
        spheres[i] = Sphere(vec3(i % 4, int(floor(i) / 4) % 4, floor(floor(i) / 4) / 4), 0.4);
    }

    Ray r = Ray(cameraPos, normalize((cameraRot * normalize(vec4(screenPos, -2, 1))).xyz));

    color = castRay(r);
}