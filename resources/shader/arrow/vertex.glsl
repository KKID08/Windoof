#version 400 core
#define M_2PI 6.283185307179586476925286766559

layout(location = 0) in float angle;
layout(location = 1) in float distance;
layout(location = 2) in float counter;

struct Point {
    float x, y, rotation, scale;
};

uniform Point start;
uniform Point end;
uniform double startTime;
uniform double duration;
uniform double currentTime;
uniform float aspectRatio;

void main() {
    float progress = (duration == 0) ? 1 : float(clamp((currentTime - startTime) / duration, 0, 1));
    vec2 arrowPos = vec2(
        mix(start.x, end.x, progress),
        mix(start.y, end.y, progress)
    );
    float pScale = mix(start.scale, end.scale, progress);
    float pRotation = mix(start.rotation, end.rotation, progress);


    // Calc Point
    float newAngle = (angle + pRotation);
    newAngle -= trunc(newAngle);
    float newDistance = distance * pScale;
    vec2 newPos = vec2(
        newDistance * cos(newAngle * M_2PI), // M_2PI = 2*M_PI = 360 * M_PI / 180
        newDistance * sin(newAngle * M_2PI)
    );
    gl_Position = vec4(arrowPos + newPos, 0.0, 1.0);
}