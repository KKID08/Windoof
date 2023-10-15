#version 330 core

/*
    distance, angle
*/

/* Rotation (Punkt finden)
    x1 = länge * cos(pi * winkel/ 180.0);
    y1 = länge * sin(pi * winkel/ 180.0);
*/

struct Point {
    float x, y, rotation, scale;
    double timestamp;
};

//layout (location = 0) in vec2 position;
layout (location = 0) in float distance;
layout (location = 1) in float angle;

uniform Point start;
uniform Point end;
uniform double currentTime;

void main() {
    // Calc Arror Position
    float progress = float((currentTime - start.timestamp) / (end.timestamp - start.timestamp));
    arrowPos = vec2(
        mix(start.x, end.x, progress),
        mix(start.y, end.y, progress)
    );
    pScale = mix(start.scale, end.scale, progress);
    pRotation = mix(start.rotation, end.rotation, progress);

    // Calc Point
    newAngle = (angle + pRotation) % 1;
    newDistance = distance * pScale;
    newPos = vec2(
        newDistance * cos(PI * newAngle * 2), // 2 = 360 / 180
        newDistance * sin(PI * newAngle * 2)
    );
    gl_FragCoord = vec4(arrowPos + newPos, 0.0, 1.0); // New Position
}