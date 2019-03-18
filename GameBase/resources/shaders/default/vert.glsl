#version 450

layout(location = 0) in vec3 vertex;
out vec3 fragVertex;

void main() {
    gl_Position = vec4(vertex, 1);
    fragVertex = vertex;
}