#version 450

in vec2 uv;

out vec4 color;

uniform sampler2D tex;

void main() {
    color = texture2D(tex, uv);
}