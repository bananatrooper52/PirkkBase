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

struct Ray {
    vec3 o;
    vec3 d;
};

void swap(inout float a, inout float b) {
    float c = a;
    a = b;
    b = c;
}

bool intersectCube(Ray r, vec3 bmin, vec3 bmax) { 
    float tmin = (bmin.x - r.o.x) / r.d.x; 
    float tmax = (bmax.x - r.o.x) / r.d.x; 
 
    if (tmin > tmax) swap(tmin, tmax); 
 
    float tymin = (bmin.y - r.o.y) / r.d.y; 
    float tymax = (bmax.y - r.o.y) / r.d.y; 
 
    if (tymin > tymax) swap(tymin, tymax); 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return false; 
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    float tzmin = (bmin.z - r.o.z) / r.d.z; 
    float tzmax = (bmax.z - r.o.z) / r.d.z; 
 
    if (tzmin > tzmax) swap(tzmin, tzmax); 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return false; 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
 
    return true; 
} 

vec4 castRay(Ray ray) {
    vec4 color = vec4(0);
    
    vec3 boxMin = vec3(-0.5, -0.5, -4);
    vec3 boxMax = vec3(0.5, 0.5, -3);

    if (intersectCube(ray, boxMin, boxMax)) return vec4(0.3, 0.4, 0.8, 1);

    return vec4(0);
}

void main() {
    color = castRay(Ray(cameraPos, (cameraRot * normalize(vec4(screenPos, -1, 1))).xyz));
}