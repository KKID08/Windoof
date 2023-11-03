#version 400 core
#define M_2PI 6.283185307179586476925286766559

layout (location = 0) in vec2 vertex;

uniform struct {
    float width;
    float height;
    float centerX;
    float centerY;
    float smoothness;
    float rotation;
} start, end;

uniform double startTime;
uniform double duration;
uniform double currentTime;
uniform float aspectRatio;

void main() {
    // Animation

    float progress = (duration == 0) ? 1 : float(clamp((currentTime - startTime) / duration, 0, 1));

    float rotation = mix(start.rotation, end.rotation, progress);
    vec2 rectange = vec2(
        mix(start.width,  end.width,  progress) * vertex.x,
        mix(start.height, end.height, progress) * vertex.y / aspectRatio
    );
    vec2 center = vec2(
        mix(start.centerX,end.centerX, progress),
        mix(start.centerY, end.centerY, progress)
    );

    // Rotate
    float distance = distance(rectange, vec2(0, 0));
    float angle = atan(rectange.y, rectange.x) - rotation;
    vec2 rotated;
    rotated.x = distance * cos(angle);
    rotated.y = distance * sin(angle);
    rotated.y *= aspectRatio;

    // Return
    gl_Position = vec4(rotated + center, 0.0, 1.0);
}