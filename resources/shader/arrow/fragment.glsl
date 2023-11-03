#version 330 core

in vec4 gl_FragCoord;

out vec4 FragColor;

uniform float currentTimeColor;

void main() {
    FragColor = vec4(pow(sin(currentTimeColor / 2 ), 2), pow(cos(currentTimeColor / 2), 2), 0.2f, 0.8f); // Orange color with transparency
}