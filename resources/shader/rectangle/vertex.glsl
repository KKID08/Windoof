#version 400 core
#define M_2PI 6.283185307179586476925286766559

layout (location = 0) in vec2 vertex;

uniform struct {
    float width;
    float height;
    float centerX;
    float centerY;
    float outlineScale;
    float rotation;
    float smoothness;
} start, end;

uniform double startTime;
uniform double duration;
uniform double currentTime;
uniform float aspectRatio;

flat out int isOutline;    // Boolean flag from the geometry shader

void main() {
    // Animation
    float progress = (duration == 0) ? 1 : float(clamp((currentTime - startTime) / duration, 0, 1));

    // Animation Mix
    float outlineScale = mix(start.outlineScale, end.outlineScale, progress);
    float rotation = mix(start.rotation, end.rotation, progress);
    vec2 rectangle = vec2(
        mix(start.width,  end.width,  progress),
        mix(start.height, end.height, progress)
    );
    vec2 center = vec2(
        mix(start.centerX,end.centerX, progress),
        mix(start.centerY, end.centerY, progress)
    );

    // Outline
    float outlineSize = outlineScale * (rectangle.x);

    vec2 internalVertex;

    if (vertex.x == 1 || vertex.x == -1) {
        isOutline = 0;
        internalVertex = vertex;
        rectangle = rectangle * internalVertex;
    } else {
        isOutline = 1;
        internalVertex = vertex * 2;
        rectangle = rectangle * internalVertex;
        rectangle.x += outlineSize * internalVertex.x;
        rectangle.y += outlineSize * internalVertex.y * aspectRatio;
    }

    // Rotate
    rectangle.y = rectangle.y / aspectRatio;
    float distance = distance(rectangle, vec2(0));
    float angle = atan(rectangle.y, rectangle.x) - rotation;
    rectangle.x = distance * cos(angle);
    rectangle.y = distance * sin(angle);
    rectangle.y *= aspectRatio;

    // Return
    gl_Position = vec4(rectangle + center, 0.0, 1.0);
}