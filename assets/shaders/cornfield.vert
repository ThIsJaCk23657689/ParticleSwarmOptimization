#version 330 core

layout (location = 0) in vec3 position;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    float temp = clamp((position.y - 0) / (150 - 0), 0.0f, 1.0f);
    color = (1 - temp) * vec3(0.14235f, 0.2454f, 0.2723) + temp * vec3(0.78438f, 0.5542046, 0.3156);
    gl_Position = projection * view * model * vec4(position, 1.0);
}