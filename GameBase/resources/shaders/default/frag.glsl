#version 450

in vec3 fragVertex;

out vec4 color;

void main() {
    color = vec4(fragVertex.xy, 0, 1);
}