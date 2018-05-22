#version 330 core

uniform int width;
uniform int height;
uniform int elapsed;

out vec3 color;
in vec3 position;

void main() {
    float aspect = float(width) / height;

    vec2 xy = vec2(position.x, position.y / aspect);

    float len = length(xy);
    float r = sin(len * 50. - elapsed/500.);
    color = vec3(smoothstep(0., 0.1, r));
}

