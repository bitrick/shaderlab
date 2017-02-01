#version 330 core

uniform int width;
uniform int height;
uniform int elapsed;

out vec3 color;
in vec3 position;

void main() {
    float coe = sin(elapsed);
    color = normalize(position + vec3(1,1,1));
}

