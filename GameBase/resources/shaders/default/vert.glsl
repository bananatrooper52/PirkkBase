#version 450

uniform float aspect;

in vec3 vertex;

out vec2 screenPos;

void main() {
    gl_Position = vec4(vertex, 1);
    screenPos = vec2(vertex.x * aspect, vertex.y);
}