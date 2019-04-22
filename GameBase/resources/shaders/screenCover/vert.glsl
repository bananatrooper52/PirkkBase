#version 450

in vec2 vertex;

out vec2 uv;

void main() {
    gl_Position = vec4(vertex, 0, 1);
    uv = vec2(vertex.x, vertex.y) * 0.5 + 0.5;
}