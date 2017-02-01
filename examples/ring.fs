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
    if (sin(len * 50 - elapsed/50) > 0) {
        color = vec3(0,0,0);
    }
    else {
        color = vec3(1,1,1);
    }
}

